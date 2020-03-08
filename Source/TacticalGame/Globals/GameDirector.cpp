// Fill out your copyright notice in the Description page of Project Settings.

#include "GameDirector.h"
#include "Kismet/GameplayStatics.h"
#include "TacticalGameGameMode.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

// Sets default values
UGameDirector::UGameDirector()
{
	UE_LOG(LogTemp, Warning, TEXT("game director created"))

}

void UGameDirector::Init()
{
	SetCamera();
	SetTileMap();
	SetSpawner();
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

void UGameDirector::SpawnCharacters(bool SnapToGrid)
{
	Spawner->SpawnCharacters(SnapToGrid);
}

void UGameDirector::SetCamera()
{
	AActor* CameraTmp = UGameplayStatics::GetActorOfClass(GetWorld(), ATopViewCamera::StaticClass());

	if (CameraTmp)
	{
		Cast<ATopViewCamera>(CameraTmp);
		Camera = Cast<ATopViewCamera>(CameraTmp);
	}
}
