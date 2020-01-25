// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"
#include "GridUtils.h"
#include "TacticalGameGameMode.h"


UBattleManager::UBattleManager()
{
	GridEnabled = true;
	CurrentState = CombatStateE::DESELECTED_STATE;
}

void UBattleManager::Init()
{
	DeselectedState = NewObject<UBSMDeselectedState>(this, TEXT("DeselectedState"));
	CharacterSelectedState = NewObject<UBSMCharacterSelectedState>(this, TEXT("CharacterSelectedState"));
	EnemyLockedState = NewObject<UBSMEnemyLockedState>(this, TEXT("EnemyLockedState"));
	TileSelectedState = NewObject<UBSMTileSelectedState>(this, TEXT("TileSelectedState"));

	DeselectedState->Init();
	CharacterSelectedState->Init();
	EnemyLockedState->Init();
	TileSelectedState->Init();

	StateMachine.Emplace(CombatStateE::DESELECTED_STATE, DeselectedState);
	StateMachine.Emplace(CombatStateE::ENEMY_LOCKED, EnemyLockedState );
	StateMachine.Emplace(CombatStateE::TILE_SELECTED, TileSelectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_SELECTED, CharacterSelectedState);

	GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());
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
		CurrentAction = StateMachine[CurrentState]->PlayState();
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
		ResetStateMachine();
	}

	// Snap Players to grid

	// Init player health and equip
}
	

void UBattleManager::EndTurn()
{
	if (!PlayerTurn)
	{
		ResetStateMachine();
	}

	PlayerTurn = !PlayerTurn;
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
		for (auto player : GameMode->Party->GetSelectedTeam())
		{
			BattleEnded &= player->CurrentHealth <= 0;
		}
	}

	return BattleEnded;
}

void UBattleManager::EndBattle()
{
	GridEnabled = false;
}

void UBattleManager::ResetStateMachine()
{
	SelectedTile = GameMode->Party->GetSelectedTeam()[0]->ActorCharacter->CurrentTile;
	GameMode->GameDirector->Camera->MoveToTile(SelectedTile);
	CurrentState = CombatStateE::DESELECTED_STATE;

	Player2Paths = TMap<FName, DijkstraOutput>();
	Player2Turn = TMap<FName, bool>();

	for (auto Char : GameMode->Party->GetSelectedTeam())
	{
		if (Char->CurrentHealth > 0)
		{
			Player2Paths.Emplace(Char->Name, UGridUtils::GetShortestPaths(Char->ActorCharacter->CurrentTile, 99));
			Player2Turn.Emplace(Char->Name, false);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%d"), Player2Paths[GameMode->Party->GetSelectedTeam()[0]->Name].Num())
}