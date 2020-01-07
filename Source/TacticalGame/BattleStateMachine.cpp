// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleStateMachine.h"
#include "TacticalGameGameMode.h"

UBattleStateMachine::UBattleStateMachine()
{
	State2Method.Emplace(CombatStateE::DESELECTED_STATE, &UBattleStateMachine::DeselectedState);
	State2Method.Emplace(CombatStateE::CHARACTER_SELECTED, &UBattleStateMachine::CharacterSelected);
	State2Method.Emplace(CombatStateE::ENEMY_LOCKED, &UBattleStateMachine::EnemyLocked);
	State2Method.Emplace(CombatStateE::TILE_SELECTED, &UBattleStateMachine::TileSelected);
}

void UBattleStateMachine::Init()
{
	ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		TileMap = GameMode->GameDirector->TileMap;
	}

	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());
	
}

UAction* UBattleStateMachine::DeselectedState()
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
	if (Input->HardAxisIsNotZero())
	{

		UE_LOG(LogTemp, Warning, TEXT("%s"), *SelectedTile->TileCenter.ToString())

		if (SelectedTile && SelectedTile->Direction2Neighbours.Contains(Input->HardAxis))
		{
			ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

			UE_LOG(LogTemp, Warning, TEXT("%s"), *SelectedTile->TileCenter.ToString())

			SelectedTile = SelectedTile->Direction2Neighbours[Input->HardAxis].Key;
			TileMap->SetCursorToTile(SelectedTile);
			GameMode->GameDirector->Camera->MoveToTile(SelectedTile);

		}
	}
	
	return nullptr;
}

UAction* UBattleStateMachine::CharacterSelected()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));

	return action;
}

UAction* UBattleStateMachine::EnemyLocked()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));

	return action;
}

UAction* UBattleStateMachine::TileSelected()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));

	return action;
}

UAction* UBattleStateMachine::PlayState()
{
	return (this->* (State2Method[CurrentState]))();
}

void UBattleStateMachine::Reset(FTile* CurrentTile)
{
	CurrentState = CombatStateE::DESELECTED_STATE;
	SelectedTile = CurrentTile;
}