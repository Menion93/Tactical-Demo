// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyAIController.h"
#include "BattleGameState.h"


ABattleGameState::ABattleGameState()
{
	GridEnabled = false;
}

void ABattleGameState::ToggleBattleMode(bool mode)
{
	GridEnabled = mode;
}

void ABattleGameState::PlayTurn()
{
	
}

void ABattleGameState::InitBattleState(Turn FirstTurn, TArray<ABaseEnemyAIController> EnemiesParam)
{
	CurrentTurn = FirstTurn;
	Enemies = EnemiesParam;
	CurrentCharacter = 0;
}