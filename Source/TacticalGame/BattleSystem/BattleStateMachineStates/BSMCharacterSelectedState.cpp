// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Engine/World.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState()
{
	
}

void UBSMCharacterSelectedState::InitState(APlayerFireTeam* SM, float MoveGridSpeed, float Delay)
{
	Super::Init(SM);
	MoveTime = 1 / MoveGridSpeed;
	DelayToSpeed = Delay;
}

bool UBSMCharacterSelectedState::InputEventX(float DeltaTime)
{
	//DisableInput(true);
	StateMachine->TransitionToState(CombatStateE::OPEN_BAG);
	return true;
}

bool UBSMCharacterSelectedState::InputEventY(float DeltaTime)
{
	return false;
}

bool UBSMCharacterSelectedState::InputEventA(float DeltaTime)
{
	FTile SelectedTile = BattleManager->GetSelectedTile();

	if (SelectedTile.IsObstacle || 
		!(
			SelectedTile.Character || 
		    SelectedTile.Pickable ||
		    StateMachine->CurrentCharacter->TileInRange(SelectedTile)
		 )
		)
	{
		return false;
	}

	StateMachine->TargetCharacter = SelectedTile.Character;
	StateMachine->TransitionToState(CombatStateE::CHARACTER_INFO);
	return true;
}

bool UBSMCharacterSelectedState::InputEventB(float DeltaTime)
{
	BattleManager->GameMode->BattleUI->HideCharacterBar();
	StateMachine->CurrentCharacter->PerimeterComponent->ShowPerimeter(false);
	StateMachine->CurrentCharacter->PathfindingComponent->ShowShortestPath(false);

	// Look at character position
	FTile CharacterTile = Grid->GetTile(StateMachine->CurrentCharacter->CurrentTileIndex);
	BattleManager->GameMode->Camera->LookAtPosition(CharacterTile.TileCenter);

	StateMachine->SelectedTile = StateMachine->CurrentCharacter->CurrentTileIndex;
	Grid->SetCursorToTile(StateMachine->SelectedTile);
	StateMachine->CurrentCharacter = nullptr;
	StateMachine->TransitionToState(CombatStateE::DESELECTED_STATE);
	return true;
}

bool UBSMCharacterSelectedState::InputEventRAxis(float DeltaTime)
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

bool UBSMCharacterSelectedState::InputEventLAxis(float DeltaTime)
{
	// Move the cursor
	if (!Input->LHardAxis.IsZero())
	{
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

				StateMachine->CurrentCharacter->PathfindingComponent->DrawShortestPath(StateMachine->SelectedTile);
				StateMachine->CurrentCharacter->PathfindingComponent->ShowShortestPath(true);

				Grid->SetCursorToTile(StateMachine->SelectedTile);
				BattleManager->GameMode->Camera->LerpToPosition(BattleManager->GetSelectedTile().TileCenter);

				if (World)
				{
					World->GetTimerManager().SetTimer(timerHandle, this, &UBSMCharacterSelectedState::ResetCooldownMovementGrid, time);
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


bool UBSMCharacterSelectedState::InputEventR2(float DeltaTime)
{
	return StateMachine->CurrentCharacter->RevertAction();
}


void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = MoveTime;
}

FVector2D UBSMCharacterSelectedState::MapInput(FVector2D OriginalInput)
{
	FVector Input3D(OriginalInput.X, OriginalInput.Y, 0);

	ATopViewCamera* Camera = BattleManager->GameMode->Camera;
	int Angle = int(Camera->YawAngle);

	float RotationAngle = (Camera->YawIndex * Angle) / (Angle * 2) * Angle * 2;
	const FRotator YawRotation(0, RotationAngle, 0);

	FVector RotatedInput3D = YawRotation.RotateVector(Input3D);

	return FVector2D(FMath::RoundToInt(RotatedInput3D.X), FMath::RoundToInt(RotatedInput3D.Y));
}

