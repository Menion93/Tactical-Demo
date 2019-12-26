// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.h"
#include "TopViewCamera.h"
#include "ATileMapSet.h"
#include "GameDirector.generated.h"

UCLASS()
class TACTICALGAME_API UGameDirector : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UGameDirector();

	ASpawner* Spawner;
	ATopViewCamera* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AATileMapSet* TileMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SpawnAtStart = true;

public:
	// Called when the game starts or when spawned
	void Init();

public:
	void SpawnCharacters();

private:
	void SetTileMap();
	void SetSpawner();


};
