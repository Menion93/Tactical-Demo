// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Engine/World.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState()
{
	
}

void UBSMCharacterSelectedState::Init(APlayerFireTeam* SM, float MoveGridSpeed, float Delay)
{
	Super::Init(SM);
	MoveTime = 1 / MoveGridSpeed;
	DelayToSpeed = Delay;
}

bool UBSMCharacterSelectedState::InputEventX()
{
	//DisableInput(true);
	StateMachine->TransitionToState(CombatStateE::OPEN_BAG);
	return true;
}

bool UBSMCharacterSelectedState::InputEventY()
{
	return false;
}

bool UBSMCharacterSelectedState::InputEventA()
{
	FTile SelectedTile = BattleManager->GetSelectedTile();

	if (SelectedTile.IsObstacle)
	{
		return false;
	}

	if (!SelectedTile.Character &&
		!SelectedTile.Pickable &&
		!StateMachine->CurrentCharacter->TileInRange(SelectedTile))
	{
		return false;
	}

	StateMachine->TransitionToState(CombatStateE::CHARACTER_INFO);
	return true;
}

bool UBSMCharacterSelectedState::InputEventB()
{
	BattleManager->GameMode->BattleUI->HideCharacterBar();
	StateMachine->CurrentCharacter->ShowPerimeter(false);
	StateMachine->CurrentCharacter->ShowShortestPath(false);

	// Look at character position
	FTile CharacterTile = Grid->GetTile(StateMachine->CurrentCharacter->CurrentTileIndex);
	BattleManager->GameMode->Camera->LookAtPosition(CharacterTile.TileCenter);

	StateMachine->SelectedTile = StateMachine->CurrentCharacter->CurrentTileIndex;
	Grid->SetCursorToTile(StateMachine->SelectedTile);
	StateMachine->CurrentCharacter = nullptr;
	StateMachine->TransitionToState(CombatStateE::DESELECTED_STATE);
	return true;
}


bool UBSMCharacterSelectedState::InputEventLAxis()
{
	// Move the cursor
	if (!Input->HardAxis.IsZero())
	{
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

				StateMachine->CurrentCharacter->DrawShortestPath(StateMachine->SelectedTile);
				StateMachine->CurrentCharacter->ShowShortestPath(true);

				Grid->SetCursorToTile(StateMachine->SelectedTile);
				BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);

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


bool UBSMCharacterSelectedState::InputEventR2()
{
	return StateMachine->CurrentCharacter->RevertAction();
}


void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = MoveTime;
}
