// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"
#include "Globals/TacticalGameGameMode.h"
#include "Engine/World.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState()
{
	
}

void UBSMCharacterSelectedState::InputEventX()
{
	//DisableInput(true);
	BattleManager->TransitionToState(CombatStateE::OPEN_BAG);
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

	BattleManager->TransitionToState(CombatStateE::CHARACTER_INFO);

}

void UBSMCharacterSelectedState::InputEventB()
{
	BattleManager->GameMode->BattleUI->HideCharacterBar();
	BattleManager->CurrentCharacter->ShowPerimeter(false);
	BattleManager->CurrentCharacter->ShowShortestPath(false);

	// Look at character position
	FTile CharacterTile = TileMap->GetTile(BattleManager->CurrentCharacter->CurrentTileIndex);
	BattleManager->GameMode->GameDirector->Camera->LookAtPosition(CharacterTile.TileCenter);

	BattleManager->SelectedTile = BattleManager->CurrentCharacter->CurrentTileIndex;
	TileMap->SetCursorToTile(BattleManager->SelectedTile);
	BattleManager->CurrentCharacter = nullptr;
	BattleManager->TransitionToState(CombatStateE::DESELECTED_STATE);
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
				ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

				BattleManager->SelectedTile = CurrentTile.Direction2Neighbours[Index].Key->Index;

				BattleManager->CurrentCharacter->DrawShortestPath(BattleManager->SelectedTile);
				BattleManager->CurrentCharacter->ShowShortestPath(true);

				TileMap->SetCursorToTile(BattleManager->SelectedTile);
				GameMode->GameDirector->Camera->LookAtPosition(BattleManager->GetCurrentTile().TileCenter);

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
