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
	
}

void ABattleGameState::InitBattleState(Turn FirstTurn)
{
	CurrentTurn = FirstTurn;
	CurrentCharacter = 0;
}