// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"


ABattleGameState::ABattleGameState()
{
	GridEnabled = true;
}

void ABattleGameState::ToggleBattleMode(bool mode)
{
	GridEnabled = mode;
}

void ABattleGameState::PlayTurn()
{
	if (PlayerTurn)
	{

	}
	else
	{
		// Handle AI Turn
	}
	
}

void ABattleGameState::InitBattleState(bool PlayerTurn)
{
	PlayerTurn = PlayerTurn;

	CurrentState = PlayerTurn ? CombatStateE::CSE_CHAR_DESELECTED : CombatStateE::CSE_ENEMY_TURN;
}
	

void ABattleGameState::EndTurn()
{
	for (auto& output : player2turn)
	{
		output.Value = false;
	}

}

bool ABattleGameState::IsTurnEnded()
{
	bool NoTurnAvailable = true;

	for (auto p2t : player2turn)
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
		for (auto player : player2turn)
		{
			BattleEnded &= player.Key->CurrentHealth <= 0;
		}
	}

	return BattleEnded;
}