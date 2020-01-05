// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"


ABattleGameState::ABattleGameState()
{
	GridEnabled = true;
	StateMachine = NewObject<UBattleStateMachine>(this, TEXT("GameDirector"));
}

void ABattleGameState::ToggleBattleMode(bool mode)
{
	GridEnabled = mode;
}

void ABattleGameState::PlayTurn()
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

			if (IsTurnEnded())
			{
				EndTurn();
			}

			CurrentAction = nullptr;
		}
	}
	// Let the player choose an action
	else if (PlayerTurn)
	{
		StateMachine->PlayState();
	}
	// Let the AI choose an action
	else
	{
		// Handle AI Turn
	}
}

void ABattleGameState::InitBattleState(bool IsPlayerTurn)
{
	PlayerTurn = IsPlayerTurn;
	GridEnabled = true;
	StateMachine->Reset();
}
	

void ABattleGameState::EndTurn()
{
	for (auto& output : Player2Turn)
	{
		output.Value = false;
	}
}

bool ABattleGameState::IsTurnEnded()
{
	bool NoTurnAvailable = true;

	for (auto p2t : Player2Turn)
	{
		NoTurnAvailable &= p2t.Value;
	}

	return NoTurnAvailable;
}

bool ABattleGameState::IsBattleEnded()
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

void ABattleGameState::EndBattle()
{
	GridEnabled = false;
}