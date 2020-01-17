// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"
#include "TacticalGameGameMode.h"
#include "BSMEnemyLockedState.h"
#include "BSMCharacterSelectedState.h"
#include "BSMDeselectedState.h"
#include "BSMTileSelectedState.h"

UBattleManager::UBattleManager()
{
	GridEnabled = true;
	CurrentState = CombatStateE::DESELECTED_STATE;
}

void UBattleManager::Init()
{
	UBSMDeselectedState* DeselectedState = NewObject<UBSMDeselectedState>(this, TEXT("DeselectedState"));
	UBSMCharacterSelectedState* CharacterSelectedState = NewObject<UBSMCharacterSelectedState>(this, TEXT("CharacterSelectedState"));
	UBSMEnemyLockedState* EnemyLockedState = NewObject<UBSMEnemyLockedState>(this, TEXT("EnemyLockedState"));
	UBSMTileSelectedState* TileSelectedState = NewObject<UBSMTileSelectedState>(this, TEXT("TileSelectedState"));

	DeselectedState->Init();
	CharacterSelectedState->Init();
	EnemyLockedState->Init();
	TileSelectedState->Init();

	State2Method.Emplace(CombatStateE::DESELECTED_STATE, DeselectedState);
	State2Method.Emplace(CombatStateE::ENEMY_LOCKED, EnemyLockedState);
	State2Method.Emplace(CombatStateE::TILE_SELECTED, TileSelectedState);
	State2Method.Emplace(CombatStateE::CHARACTER_SELECTED, CharacterSelectedState);
}


void UBattleManager::ToggleBattleMode(bool mode)
{
	GridEnabled = mode;
}

void UBattleManager::PlayTurn()
{
	// if we already chose an action
	if (CurrentAction)
	{
		// Play and see if action has ended
		if (CurrentAction->PlayAction())
		{
			if (IsBattleEnded())
			{
				EndBattle();
			} 
			else if (IsTurnEnded())
			{
				EndTurn();
			}

			CurrentAction = nullptr;
		}
	}
	// Let the player choose an action
	else if (PlayerTurn)
	{
		CurrentAction = State2Method[CurrentState]->PlayState();
	}
	// Let the AI choose an action
	else
	{
		// Handle AI Turn
	}
}

void UBattleManager::InitBattleState(bool IsPlayerTurn)
{
	PlayerTurn = IsPlayerTurn;
	GridEnabled = true;

	// Update current Tile
	if (PlayerTurn)
	{
		ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());
		ResetStateMachine(GameMode->Players[0]->ActorCharacter->CurrentTile);
		GameMode->GameDirector->Camera->MoveToTile(SelectedTile);
	}
}
	

void UBattleManager::EndTurn()
{
	for (auto& output : Player2Turn)
	{
		output.Value = false;
	}
}

bool UBattleManager::IsTurnEnded()
{
	bool NoTurnAvailable = true;

	for (auto p2t : Player2Turn)
	{
		NoTurnAvailable &= p2t.Value;
	}

	return NoTurnAvailable;
}

bool UBattleManager::IsBattleEnded()
{
	bool BattleEnded = true;

	if (PlayerTurn)
	{
		
	}
	else
	{
		for (auto player : Player2Turn)
		{
			BattleEnded &= player.Key->CurrentHealth <= 0;
		}
	}

	return BattleEnded;
}

void UBattleManager::EndBattle()
{
	GridEnabled = false;
}

void UBattleManager::ResetStateMachine(FTile* CurrentTile)
{
	CurrentState = CombatStateE::DESELECTED_STATE;
	SelectedTile = CurrentTile;
}