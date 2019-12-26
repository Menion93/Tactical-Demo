// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameDirector.h"
#include "Engine/World.h"

// Sets default values
UGameDirector::UGameDirector()
{


}

void UGameDirector::Init()
{
	SetTileMap();
	SetSpawner();

	if (SpawnAtStart)
	{
		SpawnCharacters();
	}
}

void UGameDirector::SetTileMap()
{
	AActor* TileTmp = UGameplayStatics::GetActorOfClass(GetWorld(), AATileMapSet::StaticClass());

	if (TileTmp)
	{
		TileMap = Cast<AATileMapSet>(TileTmp);
	}

}

void UGameDirector::SetSpawner()
{
	AActor* SpawnerTmp = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawner::StaticClass());

	if (SpawnerTmp)
	{
		Spawner = Cast<ASpawner>(SpawnerTmp);
	}

}

void UGameDirector::SpawnCharacters()
{
	Spawner->SpawnCharacters();
}



