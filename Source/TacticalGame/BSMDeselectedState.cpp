// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMDeselectedState.h"
#include "TacticalGameGameMode.h"
#include "Engine/World.h"


UBSMDeselectedState::UBSMDeselectedState()
{

}


UAction* UBSMDeselectedState::PlayState()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));

	// Try to select current tile
	if (Input->A)
	{

	}

	// Move Cursor to Different Character
	if (Input->PAD_UP)
	{

	}

	// Move Cursor to Different Character 
	if (Input->PAD_BOTTOM)
	{

	}

	// Move Cursor to Selected Character
	if (Input->X)
	{

	}

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
				time = 0.5;
			}

			AxisReleased = false;

			FTileIndex Index(Input->HardAxis);
			if (BattleManager->SelectedTile && BattleManager->SelectedTile->Direction2Neighbours.Contains(Index))
			{
				ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

				BattleManager->SelectedTile = BattleManager->SelectedTile->Direction2Neighbours[Index].Key;
				TileMap->SetCursorToTile(BattleManager->SelectedTile);
				GameMode->GameDirector->Camera->MoveToTile(BattleManager->SelectedTile);

				if (World)
				{
					World->GetTimerManager().SetTimer(timerHandle, this, &UBSMDeselectedState::ResetCooldownMovementGrid, time);
				}

				CooldownMovementGrid = true;
			}
		}
	}
	else
	{
		AxisReleased = true;
	}

	return nullptr;
}

void UBSMDeselectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}

//UAction* UBattleStateMachine::CharacterSelected()
//{
//	UAction* action = NewObject<UAction>(this, TEXT("Action"));
//
//	return action;
//}
//
//UAction* UBattleStateMachine::EnemyLocked()
//{
//	UAction* action = NewObject<UAction>(this, TEXT("Action"));
//
//	return action;
//}
//
//UAction* UBattleStateMachine::TileSelected()
//{
//	UAction* action = NewObject<UAction>(this, TEXT("Action"));
//
//	return action;
//}