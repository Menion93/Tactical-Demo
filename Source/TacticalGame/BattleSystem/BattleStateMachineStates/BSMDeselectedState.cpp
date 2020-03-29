// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMDeselectedState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Engine/World.h"


UBSMDeselectedState::UBSMDeselectedState()
{

}

void UBSMDeselectedState::Init(APlayerFireTeam* SM, float MoveGridSpeed, float Delay)
{
	Super::Init(SM);
	MoveTime = 1 / MoveGridSpeed;
	DelayToSpeed = Delay;
}


bool UBSMDeselectedState::InputEventX()
{
	return false;
}

bool UBSMDeselectedState::InputEventY()
{
	return false;
}

// When selecting a Tile
bool UBSMDeselectedState::InputEventA()
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
			Character->ShowPerimeter(true);
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

bool UBSMDeselectedState::InputEventB()
{
	return false;
}


bool UBSMDeselectedState::InputEventLAxis()
{

	if (!Input->HardAxis.IsZero()) {

		if (!CooldownMovementGrid || Input->Axis_DOWN)
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

			if (FMath::Abs(Input->Axis.X) >= FMath::Abs(Input->Axis.Y))
			{
				Direction = FVector2D(FMath::RoundToInt(Input->Axis.X), 0);
			}
			else
			{
				Direction = FVector2D(0, FMath::RoundToInt(Input->Axis.Y));
			}

			FTileIndex Index(Direction);
			FTile CurrentTile = BattleManager->GetSelectedTile();

			if (CurrentTile.Direction2Neighbours.Contains(Index))
			{
				StateMachine->SelectedTile = CurrentTile.Direction2Neighbours[Index].Key->Index;
				Grid->SetCursorToTile(StateMachine->SelectedTile);
				BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);

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

bool UBSMDeselectedState::InputEventR1()
{
	TArray<AGCharacter*> AvailableCharacters = StateMachine->Characters.FilterByPredicate([](auto& Char) 
	{
		return Char->State->CurrentActionPoints > 0;
	});

	StateMachine->SelectionIndex = (StateMachine->SelectionIndex + 1) % AvailableCharacters.Num();

	AGCharacter* Character = AvailableCharacters[StateMachine->SelectionIndex];
	
	StateMachine->SelectedTile = Character->CurrentTileIndex;
	Grid->SetCursorToTile(StateMachine->SelectedTile);
	BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);
	return true;
}

bool UBSMDeselectedState::InputEventL1()
{
	TArray<AGCharacter*> AvailableCharacters = StateMachine->Characters.FilterByPredicate([](auto& Char)
	{
		return Char->State->CurrentActionPoints > 0;
	});

	StateMachine->SelectionIndex = (StateMachine->SelectionIndex - 1) % AvailableCharacters.Num();

	if (StateMachine->SelectionIndex < 0)
	{
		StateMachine->SelectionIndex = AvailableCharacters.Num() - 1;
	}

	AGCharacter* Character = AvailableCharacters[StateMachine->SelectionIndex];

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