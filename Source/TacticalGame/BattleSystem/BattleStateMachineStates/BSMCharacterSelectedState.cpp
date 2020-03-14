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
	BattleManager->GameMode->BattleUI->OpenBag();
	BattleManager->CurrentState = CombatStateE::CHARACTER_INFO;
}

void UBSMCharacterSelectedState::InputEventY()
{
	
}

void UBSMCharacterSelectedState::InputEventA()
{
	FTile* SelectedTile = BattleManager->SelectedTile;

	if (SelectedTile && SelectedTile->IsObstacle)
	{
		return;
	}

	AGCharacter* Character = SelectedTile->Character;

	if (Character)
	{
		//DisableInput(true);
		BattleManager->GameMode->BattleUI->OpenActionMenu(BattleManager->CurrentCharacter, Character, *SelectedTile);
		BattleManager->CurrentState = CombatStateE::CHARACTER_INFO;
	}

	if (BattleManager->CurrentCharacter->TileInRange(SelectedTile))
	{
		//DisableInput(true);
		BattleManager->GameMode->BattleUI->OpenActionMenu(BattleManager->CurrentCharacter, nullptr, *SelectedTile);
		BattleManager->CurrentState = CombatStateE::CHARACTER_INFO;
	}
}

void UBSMCharacterSelectedState::InputEventB()
{
	BattleManager->GameMode->BattleUI->HideCharacterBar();
	BattleManager->CurrentCharacter->ShowPerimeter(false);
	BattleManager->CurrentCharacter->ShowShortestPath(false);
	BattleManager->CurrentCharacter = nullptr;
	BattleManager->CurrentState = CombatStateE::DESELECTED_STATE;
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
			if (BattleManager->SelectedTile && BattleManager->SelectedTile->Direction2Neighbours.Contains(Index))
			{
				ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

				BattleManager->SelectedTile = BattleManager->SelectedTile->Direction2Neighbours[Index].Key;
				BattleManager->CurrentCharacter->DrawShortestPath(BattleManager->SelectedTile);
				BattleManager->CurrentCharacter->ShowShortestPath(true);

				TileMap->SetCursorToTile(BattleManager->SelectedTile);
				GameMode->GameDirector->Camera->MoveToTile(BattleManager->SelectedTile);

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




void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}