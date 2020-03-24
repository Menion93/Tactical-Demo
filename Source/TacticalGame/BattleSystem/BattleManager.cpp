// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"
#include "Utils/GridUtils.h"
#include "Globals/TacticalGameGameMode.h"


UBattleManager::UBattleManager()
{
	CurrentState = CombatStateE::DESELECTED_STATE;
}

void UBattleManager::Init()
{
	DeselectedState = NewObject<UBSMDeselectedState>(this, TEXT("DeselectedState"));
	CharacterSelectedState = NewObject<UBSMCharacterSelectedState>(this, TEXT("CharacterSelectedState"));
	CharacterInfoState = NewObject<UBSMCharacterInfoState>(this, TEXT("CharacterInfoState"));
	BagState = NewObject<UBSMBagState>(this, TEXT("BagState"));
	SelectEnemyState = NewObject<UBSMSelectEnemyState>(this, TEXT("SelectEnemyState"));
	SelectAttackState = NewObject<UBSMSelectAttackState>(this, TEXT("SelectAttackState"));

	DeselectedState->Init();
	CharacterSelectedState->Init();
	CharacterInfoState->Init();
	BagState->Init();
	SelectEnemyState->Init();
	SelectAttackState->Init();

	StateMachine.Emplace(CombatStateE::DESELECTED_STATE, DeselectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_SELECTED, CharacterSelectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_INFO, CharacterInfoState);
	StateMachine.Emplace(CombatStateE::OPEN_BAG, BagState);
	StateMachine.Emplace(CombatStateE::SELECT_ATTACK, SelectAttackState);
	StateMachine.Emplace(CombatStateE::SELECT_ENEMY, SelectEnemyState);

	GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

	TileMap = GameMode->GameDirector->TileMap;
}

void UBattleManager::ToggleBattleMode(bool mode)
{

}

void UBattleManager::PlayTurn()
{
	// if we already chose an action
	if (CurrentAction)
	{
		// Play and see if action has ended
		if (CurrentAction->PlayAction())
		{
			CurrentAction->OnEnd();

			if (CurrentAction->ReversibleAction)
			{
				CurrentCharacter->ActionsBuffer.Add(CurrentAction);
			}
			else
			{
				CurrentCharacter->ActionsBuffer.Empty();
			}

			if (IsBattleEnded())
			{
				EndBattle();
			} 

			else if (IsTurnEnded())
			{
				EndTurn();
			}

			if (CurrentCharacter)
			{
				if (CurrentCharacter->State->CurrentActionPoints > 0)
				{
					CurrentState = CombatStateE::CHARACTER_SELECTED;
				}
				else
				{
					CurrentState = CombatStateE::DESELECTED_STATE;
				}
			}

			CurrentAction = nullptr;
		}
	}
	// Let the player choose an action
	else if (PlayerTurn)
	{
		if (!StateMachine[CurrentState]->IsInputDisabled())
		{
			StateMachine[CurrentState]->PlayState();
		}
	}
	// Let the AI choose an action
	else
	{
		// Handle AI Turn
	}
}

void UBattleManager::InitBattleState(bool IsPlayerTurn, bool ForceEngage)
{
	PlayerTurn = IsPlayerTurn;

	TArray<UCharacterState*> Characters = GameMode->Party->GetTeam();
	 
	for (auto character : Characters)
	{
		GameMode->GameDirector->TileMap->SnapToGrid(character->ActorCharacter);
		character->ActorCharacter->ComputeShortestPaths();
		character->ActorCharacter->ComputePerimeterPoints();
	}

	// Update current Tile
	if (PlayerTurn)
	{
		ResetToPlayerTurn();
	} 
	else
	{
		BattleEngaged = true;
	}

	BattleEngaged |= ForceEngage;

	// Snap Players to grid


	// Init player health and equip
}
	

void UBattleManager::EndTurn()
{
	if (!PlayerTurn)
	{
		ResetToPlayerTurn();
	}

	PlayerTurn = !PlayerTurn;
}

bool UBattleManager::IsTurnEnded()
{
	bool ArePointsLeft = false;

	for (auto character : GameMode->Party->GetTeam())
	{
		ArePointsLeft |= character->CurrentActionPoints > 0;
	}

	return ArePointsLeft;
}

bool UBattleManager::IsBattleEnded()
{
	bool BattleEnded = true;

	if (PlayerTurn)
	{
		
	}
	else
	{
		for (auto player : GameMode->Party->GetTeam())
		{
			BattleEnded &= player->CurrentHealth <= 0;
		}
	}

	return BattleEnded;
}

void UBattleManager::EndBattle()
{

}

void UBattleManager::ResetToPlayerTurn()
{
	SelectedTile = GameMode->Party->GetTeam()[0]->ActorCharacter->CurrentTileIndex;
	GameMode->GameDirector->TileMap->SetCursorToTile(SelectedTile);
	GameMode->GameDirector->Camera->LookAtPosition(TileMap->GetTile(SelectedTile).TileCenter);

	CurrentState = CombatStateE::DESELECTED_STATE;

	for (auto Char : GameMode->Party->GetTeam())
	{
		if (Char->CurrentHealth > 0)
		{
			// reset action points
			Char->ResetActionPoints();
		}
	}

}

void UBattleManager::SetAction(UAction* Action)
{
	CurrentAction = Action;
	Action->OnEnter();
}

void UBattleManager::TransitionToState(CombatStateE State)
{
	CurrentState = State;
	StateMachine[CurrentState]->OnEnter();
}

FTile UBattleManager::GetCurrentTile()
{
	return TileMap->GetTile(SelectedTile);
}
