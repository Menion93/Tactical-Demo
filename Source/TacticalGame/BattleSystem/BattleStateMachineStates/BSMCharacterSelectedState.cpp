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
	FTile* SelectedTile = BattleManager->SelectedTile;

	if (SelectedTile && SelectedTile->IsObstacle)
	{
		return;
	}

	AGCharacter* Character = SelectedTile->Character;

	if (Character)
	{
		TArray<UAction*> ActionList = GetActionEntryList();

		BattleManager->GameMode->BattleUI->OpenActionMenu(
			BattleManager->CurrentCharacter,
			Character, 
			*SelectedTile, 
			ActionList);
		BattleManager->TransitionToState(CombatStateE::CHARACTER_INFO);
	}

	if (BattleManager->CurrentCharacter->TileInRange(SelectedTile))
	{
		TArray<UAction*> ActionList = GetActionEntryList();

		BattleManager->GameMode->BattleUI->OpenActionMenu(
			BattleManager->CurrentCharacter,
			nullptr, 
			*SelectedTile,
			ActionList);
		BattleManager->TransitionToState(CombatStateE::CHARACTER_INFO);
	}
}

void UBSMCharacterSelectedState::InputEventB()
{
	BattleManager->GameMode->BattleUI->HideCharacterBar();
	BattleManager->CurrentCharacter->ShowPerimeter(false);
	BattleManager->CurrentCharacter->ShowShortestPath(false);
	BattleManager->GameMode->GameDirector->Camera->MoveToTile(BattleManager->CurrentCharacter->CurrentTile);
	BattleManager->SelectedTile = BattleManager->CurrentCharacter->CurrentTile;
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

void UBSMCharacterSelectedState::InputEventR2()
{
	BattleManager->CurrentCharacter->ReverseAction();
}


void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}

TArray<UAction*> UBSMCharacterSelectedState::GetActionEntryList()
{
	TArray<TSubclassOf<class UAction>> ActionList = BattleManager->GameMode->BattleUI->ActionMenu->MenuActions;

	TArray<UAction*> ActionMenuEntries;

	for (auto& ActionMenuClass : ActionList)
	{
		UAction* Action = NewObject<UAction>(
			this, 
			ActionMenuClass->GetFName(),
			RF_NoFlags, 
			ActionMenuClass.GetDefaultObject());

		if (Action->CanExecuteAction())
		{
			ActionMenuEntries.Add(Action);
		}
	}

	return ActionMenuEntries;
}
