// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"
#include "Utils/GridUtils.h"
#include "Globals/TacticalGameMode.h"


ABattleManager::ABattleManager()
{

}

void ABattleManager::Init()
{
	GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	Grid = GameMode->Grid;
}


void ABattleManager::PlayTurn()
{
	// if we already chose an action
	if (GlobalAction)
	{
		GlobalAction = CurrentAction->PlayAction() ? CurrentAction : nullptr;
	}
	else if (CurrentAction)
	{
		bool HasActionEnded = CurrentAction->PlayAction();

		if (HasActionEnded)
		{
			CurrentAction->OnEnd();

			Teams[TeamIndex]->OnActionEnd();

			if (Teams[TeamIndex]->IsWinConditionSatisfied())
			{
				EndBattle();
			}
			else if (Teams[TeamIndex]->IsTurnEnded())
			{
				EndTurn();
			}

			CurrentAction = nullptr;
		}
	}
	// Let the player choose an action
	else
	{
		if (PrevTeamIndex != TeamIndex)
		{
			PrevTeamIndex = TeamIndex;
			Teams[TeamIndex]->OnTurnStart();
		}

		Teams[TeamIndex]->PlayTurn();
	}

}

void ABattleManager::InitBattleState(bool IsPlayerTurn, bool ForceEngage)
{
	for (auto& Team : Teams)
	{
		Team->Init(this);
		Team->SpawnTeam();
	}
}


void ABattleManager::EndTurn()
{
	TeamIndex = (TeamIndex + 1) % Teams.Num();

	// Play Cool Animations & Sounds
}


void ABattleManager::EndBattle()
{

}


void ABattleManager::SetAction(UAction* Action)
{
	CurrentAction = Action;
	Action->OnEnter();
}


FTile ABattleManager::GetCurrentTile()
{
	return Grid->GetTile(SelectedTile);
}

AFireTeam* ABattleManager::GetPlayerFireTeam()
{
	return Teams[0];
}