// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMDeselectedState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "TopViewCamera.h"
#include "Engine/World.h"


UBSMDeselectedState::UBSMDeselectedState()
{

}

void UBSMDeselectedState::InitState(APlayerFireTeam* SM, float MoveGridSpeed, float Delay)
{
	Super::Init(SM);
	MoveTime = 1 / MoveGridSpeed;
	DelayToSpeed = Delay;
}


bool UBSMDeselectedState::InputEventX(float DeltaTime)
{
	return false;
}

bool UBSMDeselectedState::InputEventY(float DeltaTime)
{
	return false;
}

// When selecting a Tile
bool UBSMDeselectedState::InputEventA(float DeltaTime)
{
	AGCharacter* Character = BattleManager->GetSelectedTile().Character;

	if (Character)
	{
		// if is a controllable character
		if (StateMachine->InFireTeam(Character))
		{
			if (Character->State->CurrentActionPoints < 1)
			{
				return false;
			}

			BattleManager->GameMode->BattleUI->SetCharacterBar(Character->State);
			Character->Selected();
			Character->PerimeterComponent->ShowPerimeter(true);
			StateMachine->CurrentCharacter = Character;
			StateMachine->TransitionToState(CombatStateE::CHARACTER_SELECTED);
			return true;
		}
		// Otherwise show character info
		else
		{
			StateMachine->TargetCharacter = Character;
			StateMachine->TransitionToState(CombatStateE::CHARACTER_INFO);
			return true;
		}
	}

	return false;
}

bool UBSMDeselectedState::InputEventB(float DeltaTime)
{
	return false;
}

bool UBSMDeselectedState::InputEventRAxis(float DeltaTime)
{
	ATopViewCamera* Camera = BattleManager->GameMode->Camera;

	if (Camera->IsPanLerping) return false;
	if (Camera->IsYawLerping) return true;

	if (!Input->RAxis.IsZero())
	{
		// Compute Pitch Angle
		float PitchDirection = Input->RAxis.Y;

		if (FMath::Abs(PitchDirection) > 0.5)
		{
			Camera->ComputePitchRotation(PitchDirection, DeltaTime);
			return true;
		}

		float YawDirection = Input->RAxis.X;

		if (FMath::Abs(YawDirection) > 0.5)
		{
			Camera->ComputeYawRotation(YawDirection);
			return true;
		}
	}

	return false;
}

bool UBSMDeselectedState::InputEventLAxis(float DeltaTime)
{

	if (!Input->LHardAxis.IsZero()) {

		if (!CooldownMovementGrid)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				World->GetTimerManager().ClearTimer(timerHandle);
			}

			if (AxisReleased)
			{
				time = DelayToSpeed;
			}

			AxisReleased = false;

			FVector2D Direction;

			if (FMath::Abs(Input->LAxis.X) >= FMath::Abs(Input->LAxis.Y))
			{
				Direction = FVector2D(FMath::RoundToInt(Input->LAxis.X), 0);
			}
			else
			{
				Direction = FVector2D(0, FMath::RoundToInt(Input->LAxis.Y));
			}

			Direction = MapInput(Direction);

			FTileIndex Index(Direction);
			FTile CurrentTile = BattleManager->GetSelectedTile();

			if (CurrentTile.Direction2Neighbours.Contains(Index))
			{
				StateMachine->SelectedTile = CurrentTile.Direction2Neighbours[Index].Key->Index;
				Grid->SetCursorToTile(StateMachine->SelectedTile);
				BattleManager->GameMode->Camera->LerpToPosition(BattleManager->GetSelectedTile().TileCenter);

				if (World)
				{
					World->GetTimerManager().SetTimer(timerHandle, this, &UBSMDeselectedState::ResetCooldownMovementGrid, time);
				}

				CooldownMovementGrid = true;
				return true;
			}
		}
	}	
	else
	{
		AxisReleased = true;
		return false;
	}

	return false;
}

bool UBSMDeselectedState::InputEventR1(float DeltaTime)
{
	TArray<AGCharacter*> AvailableCharacters = StateMachine->Characters.FilterByPredicate([](auto& Char) 
	{
		return Char->State->CurrentActionPoints > 0 && Char->State->CurrentHealth > 0;
	});

	AGCharacter* Character = nullptr;
	bool Increment = true;

	while (Increment)
	{
		Increment = false;
		StateMachine->SelectionIndex = (StateMachine->SelectionIndex + 1) % AvailableCharacters.Num();

		Character = AvailableCharacters[StateMachine->SelectionIndex];
		
		FTile SelectedTile = BattleManager->Grid->GetTile(StateMachine->SelectedTile);
		if (SelectedTile.Character == Character)
		{
			if (AvailableCharacters.Num() == 1) break;

			Increment = true;
		}
	}
	
	StateMachine->SelectedTile = Character->CurrentTileIndex;
	Grid->SetCursorToTile(StateMachine->SelectedTile);
	BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);
	return true;
}

bool UBSMDeselectedState::InputEventL1(float DeltaTime)
{
	TArray<AGCharacter*> AvailableCharacters = StateMachine->Characters.FilterByPredicate([](auto& Char)
	{
		return Char->State->CurrentActionPoints > 0;
	});

	AGCharacter* Character = nullptr;
	bool Decrement = true;
	
	while (Decrement)
	{
		Decrement = false;

		StateMachine->SelectionIndex = (StateMachine->SelectionIndex - 1) % AvailableCharacters.Num();

		if (StateMachine->SelectionIndex < 0)
		{
			StateMachine->SelectionIndex = AvailableCharacters.Num() - 1;
		}

		Character = AvailableCharacters[StateMachine->SelectionIndex];

		FTile SelectedTile = BattleManager->Grid->GetTile(StateMachine->SelectedTile);
		if (SelectedTile.Character == Character)
		{
			if (AvailableCharacters.Num() == 1) break;

			Decrement = true;
		}
	}


	StateMachine->SelectedTile = Character->CurrentTileIndex;
	Grid->SetCursorToTile(StateMachine->SelectedTile);
	BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);
	return true;
}

void UBSMDeselectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = MoveTime;
}

FVector2D UBSMDeselectedState::MapInput(FVector2D OriginalInput)
{
	FVector Input3D(OriginalInput.X, OriginalInput.Y, 0);

	ATopViewCamera* Camera = BattleManager->GameMode->Camera;
	int Angle = int(Camera->YawAngle);

	float RotationAngle = (Camera->YawIndex * Angle) / (Angle * 2) * Angle * 2;
	const FRotator YawRotation(0, RotationAngle, 0);

	FVector RotatedInput3D = YawRotation.RotateVector(Input3D);

	return FVector2D(FMath::RoundToInt(RotatedInput3D.X), FMath::RoundToInt(RotatedInput3D.Y));
}
