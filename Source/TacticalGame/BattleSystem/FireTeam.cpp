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
	return true;
}

bool AFireTeam::IsWinConditionSatisfied_Implementation()
{
	return false;
}

void AFireTeam::PlayTurn_Implementation()
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
	for(auto& Character : Characters)
	{
		BattleManager->Grid->SnapToGrid(Character);

		UCharacterState* CharacterState = NewObject<UCharacterState>(
			this, Character->StateClass->GetFName(), RF_NoFlags, Character->StateClass.GetDefaultObject());

		Character->Init();
		Character->State = CharacterState;

		Character->ComputeShortestPaths();
		Character->ComputePerimeterPoints();
	}

	int PointIndex = 0;
	for (auto& SpawnPoint : SpawnPoints)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			UCharacterState* CharacterState = NewObject<UCharacterState>(
				this, CharacterClasses[PointIndex]->GetFName(), RF_NoFlags, CharacterClasses[PointIndex].GetDefaultObject());

			AGCharacter* Character = World->SpawnActor<AGCharacter>(
				CharacterState->ActorCharacterClass,
				SpawnPoint->GetActorLocation(),
				FRotator::ZeroRotator);

			Character->Init();
			CharacterState->ActorCharacter = Character;
			Character->State = CharacterState;

			FTile* Tile = BattleManager->Grid->SnapToGrid(Character);

			Characters.Add(Character);

			Character->ComputeShortestPaths();
			Character->ComputePerimeterPoints();
		}
	}
}


