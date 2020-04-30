// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"
#include "Utils/GridUtils.h"
#include "FireTeam.h"
#include "Globals/TacticalGameMode.h"


ABattleManager::ABattleManager()
{

}

void ABattleManager::Init()
{
	GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	Grid = GameMode->Grid;
}


void ABattleManager::PlayTurn(float DeltaTime)
{
	// if we already chose an action
	if (GlobalAction)
	{
		GlobalAction = CurrentAction->PlayAction(DeltaTime) ? CurrentAction : nullptr;
	}
	else if (CurrentAction)
	{
		bool HasActionEnded = CurrentAction->PlayAction(DeltaTime);

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

		Teams[TeamIndex]->PlayTurn(DeltaTime);
	}

}

void ABattleManager::InitBattleState()
{
	for (auto& Team : Teams)
	{
		Team->Init(this);
		Team->SpawnTeam();
	}

	for (auto& Team : Teams)
	{
		Team->RecomputeAllCharactersMetadata();
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


FTile ABattleManager::GetSelectedTile()
{
	return Grid->GetTile(Teams[TeamIndex]->SelectedTile);
}

AGCharacter* ABattleManager::GetCurrentCharacter()
{
	return Teams[TeamIndex]->CurrentCharacter;
}

AFireTeam* ABattleManager::GetCurrentFireTeam()
{
	return Teams[TeamIndex];
}

TArray<AFireTeam*> ABattleManager::GetHostileFireTeams(AFireTeam* FireTeam)
{
	TArray<AFireTeam*> Result;

	for (auto& FT : Teams)
	{
		if (FT != FireTeam)
		{
			bool foundAlliance = false;
			for (auto& Alliance : Alliances)
			{
				if (Alliance.Array.Contains(FT) && Alliance.Array.Contains(FireTeam))
				{
					foundAlliance = true;
				} 
			}
			if (!foundAlliance)
			{
				Result.Add(FT);
			}
		}
	}

	return Result;
}

TArray<AFireTeam*> ABattleManager::GetAlliedFireTeams(AFireTeam* FireTeam)
{
	TArray<AFireTeam*> AlliedFTs;
	AlliedFTs.Add(FireTeam);

	for (auto& FT : Teams)
	{
		if (FT != FireTeam)
		{
			bool foundAlliance = false;
			for (auto& Alliance : Alliances)
			{
				if (Alliance.Array.Contains(FT) && Alliance.Array.Contains(FireTeam))
				{
					foundAlliance = true;
				}
			}
			if (foundAlliance)
			{
				AlliedFTs.Add(FT);
			}
		}
	}

	return AlliedFTs;
}

bool ABattleManager::IsHostile(AFireTeam* FireTeam, AGCharacter* Character)
{
	TArray<AFireTeam*> HostileFTs = GetHostileFireTeams(FireTeam);

	for (auto& FT : HostileFTs)
	{
		for (auto& Char : FT->Characters)
		{
			if (Char == Character)
			{
				return true;
			}
		}
	}

	return false;
}

bool ABattleManager::IsAlly(AFireTeam* FireTeam, AGCharacter* Character)
{
	TArray<AFireTeam*> AlliedFTs = GetAlliedFireTeams(FireTeam);
	AlliedFTs.Add(FireTeam);

	for (auto& FT : AlliedFTs)
	{
		for (auto& Char : FT->Characters)
		{
			if (Char == Character)
			{
				return true;
			}
		}
	}

	return false;
}
