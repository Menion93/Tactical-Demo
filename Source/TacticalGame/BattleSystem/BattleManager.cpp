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

	DeselectedState->Init();
	CharacterSelectedState->Init();
	CharacterInfoState->Init();

	StateMachine.Emplace(CombatStateE::DESELECTED_STATE, DeselectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_SELECTED, CharacterSelectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_INFO, CharacterInfoState);

	GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());
}

void UBattleManager::ToggleBattleMode(bool mode)
{

}

void UBattleManager::PlayTurn()
{
	// if we already chose an action
	if (CurrentAction.IsBound())
	{
		CurrentAction.ExecuteIfBound();
		// Play and see if action has ended
		if (HasActionEnded)
		{
			if (IsBattleEnded())
			{
				EndBattle();
			} 

			else if (IsTurnEnded())
			{
				EndTurn();
			}

			CurrentAction.Unbind();
			HasActionEnded = false;
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

	TArray<UCharacterState*> Characters = GameMode->Party->GetSelectedTeam();
	 
	for (auto character : Characters)
	{
		character->ActorCharacter->ComputeShortestPaths();
		character->ActorCharacter->ComputePerimeterPoints(character->MovementSpeed);
		GameMode->GameDirector->TileMap->SnapToGrid(character->ActorCharacter);
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

	for (auto character : GameMode->Party->GetSelectedTeam())
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
		for (auto player : GameMode->Party->GetSelectedTeam())
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
	SelectedTile = GameMode->Party->GetSelectedTeam()[0]->ActorCharacter->CurrentTile;
	GameMode->GameDirector->TileMap->SetCursorToTile(SelectedTile);
	GameMode->GameDirector->Camera->MoveToTile(SelectedTile);
	CurrentState = CombatStateE::DESELECTED_STATE;

	for (auto Char : GameMode->Party->GetSelectedTeam())
	{
		if (Char->CurrentHealth > 0)
		{
			// reset action points
			Char->ResetActionPoints();
		}
	}

}

void UBattleManager::EndCurrentAction()
{
	HasActionEnded = true;
}

UBattleManager::Action UBattleManager::GetActionDelegate()
{
	return CurrentAction;
}