// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.h"
#include "TopViewCamera.h"
#include "Grid/ATileMapSet.h"
#include "GameDirector.generated.h"

class ATacticalGameGameMode;

UCLASS(Blueprintable, BlueprintType)
class TACTICALGAME_API UGameDirector : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UGameDirector();	

	UPROPERTY()
	ASpawner* Spawner;

	UPROPERTY()
	ATopViewCamera* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AATileMapSet* TileMap;

	UWorld* World = nullptr;

public:
	// Called when the game starts or when spawned
	void Init();

public:
	void SpawnCharacters(bool SnapToGrid);

private:
	void SetTileMap();
	void SetSpawner();
	void SetCamera();
};
