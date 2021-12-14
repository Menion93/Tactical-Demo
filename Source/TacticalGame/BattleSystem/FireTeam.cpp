// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTeam.h"
#include "BattleManager.h"
#include "Characters/CharacterState.h"

AFireTeam::AFireTeam()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AFireTeam::Init_Implementation(ABattleManager* BM)
{
	BattleManager = BM;
}

bool AFireTeam::IsTurnEnded_Implementation()
{
	bool AllFinished = true;

	for (auto& Character : Characters)
	{
		AllFinished = AllFinished && Character->State->CurrentActionPoints < 1;
	}

	return AllFinished;
}

void AFireTeam::OnTurnEnd_Implementation()
{

}


bool AFireTeam::IsWinConditionSatisfied_Implementation()
{
	TArray<AFireTeam*> FTs = BattleManager->GetHostileFireTeams(this);
	bool EnemyAlive = false;

	for (auto& FT : FTs)
	{
		for (auto& Char : FT->Characters)
		{
			if (Char != nullptr && Char->State->CurrentHealth > 0)
			{
				EnemyAlive = true;
				break;
			}
		}
	}

	return !EnemyAlive;
}

void AFireTeam::PlayTurn_Implementation(float DeltaTime)
{

}

void AFireTeam::OnActionEnd_Implementation()
{

}

void AFireTeam::OnTurnStart_Implementation()
{

}

bool AFireTeam::InFireTeam(AGCharacter* Character)
{
	return Characters.ContainsByPredicate([Character](auto& Elem) {
		return Elem->State->Name == Character->State->Name;
	});
}

void AFireTeam::SetFireTeam(TArray<AGCharacter*> FireTeam)
{
	Characters = FireTeam;
}

void AFireTeam::SpawnTeam()
{
	int i = 0;
	for(auto& Character : Characters)
	{
		BattleManager->Grid->SnapToGrid(Character);

		FString className;
		Character->StateClass->GetName(className);
		className = className + FString::FromInt(i);

		UCharacterState* CharacterState = NewObject<UCharacterState>(
			this, FName(*className), RF_NoFlags, Character->StateClass.GetDefaultObject());

		CharacterState->ActorCharacter = Character;
		CharacterState->LoadDefaultState();

		Character->Init(this, CharacterState);
		i++;
	}

}

void AFireTeam::RecomputeAllCharactersMetadata()
{
	for (auto& Character : Characters)
	{
		Character->ComputeShortestPaths();
		Character->ComputePerimeterPoints();
		Character->ComputeLoS();
	}
}

void AFireTeam::RegisterDeath(AGCharacter* DeadCharacter)
{
	Characters.Remove(DeadCharacter);
	BattleManager->Grid->RemoveCharFromTile(DeadCharacter->CurrentTileIndex);
	BattleManager->RecomputeAllCharactersMetadata();
}


void AFireTeam::EndCharacterTurn() {}




