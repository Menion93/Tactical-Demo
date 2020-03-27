// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Engine/World.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState()
{
	
}

void UBSMCharacterSelectedState::InputEventX()
{
	//DisableInput(true);
	StateMachine->TransitionToState(CombatStateE::OPEN_BAG);
}

void UBSMCharacterSelectedState::InputEventY()
{
	
}

void UBSMCharacterSelectedState::InputEventA()
{
	FTile SelectedTile = BattleManager->GetCurrentTile();

	if (SelectedTile.IsObstacle)
	{
		return;
	}

	if (!SelectedTile.Character &&
		!SelectedTile.Pickable &&
		!BattleManager->CurrentCharacter->TileInRange(SelectedTile))
	{
		return;
	}

	StateMachine->TransitionToState(CombatStateE::CHARACTER_INFO);

}

void UBSMCharacterSelectedState::InputEventB()
{
	BattleManager->GameMode->BattleUI->HideCharacterBar();
	BattleManager->CurrentCharacter->ShowPerimeter(false);
	BattleManager->CurrentCharacter->ShowShortestPath(false);

	// Look at character position
	FTile CharacterTile = Grid->GetTile(BattleManager->CurrentCharacter->CurrentTileIndex);
	BattleManager->GameMode->Camera->LookAtPosition(CharacterTile.TileCenter);

	BattleManager->SelectedTile = BattleManager->CurrentCharacter->CurrentTileIndex;
	Grid->SetCursorToTile(BattleManager->SelectedTile);
	BattleManager->CurrentCharacter = nullptr;
	StateMachine->TransitionToState(CombatStateE::DESELECTED_STATE);
}


void UBSMCharacterSelectedState::InputEventLAxis()
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
				time = 0.25;
			}

			AxisReleased = false;

			FTileIndex Index(Input->HardAxis);
			FTile CurrentTile = BattleManager->GetCurrentTile();

			if (CurrentTile.Direction2Neighbours.Contains(Index))
			{
				ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());

				BattleManager->SelectedTile = CurrentTile.Direction2Neighbours[Index].Key->Index;

				BattleManager->CurrentCharacter->DrawShortestPath(BattleManager->SelectedTile);
				BattleManager->CurrentCharacter->ShowShortestPath(true);

				Grid->SetCursorToTile(BattleManager->SelectedTile);
				GameMode->Camera->LookAtPosition(BattleManager->GetCurrentTile().TileCenter);

				if (World)
				{
					World->GetTimerManager().SetTimer(timerHandle, this, &UBSMCharacterSelectedState::ResetCooldownMovementGrid, time);
				}

				CooldownMovementGrid = true;
			}
		}
	}
	else
	{
		AxisReleased = true;
	}
}

void UBSMCharacterSelectedState::InputEventR2()
{
	BattleManager->CurrentCharacter->ReverseAction();
}


void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}
