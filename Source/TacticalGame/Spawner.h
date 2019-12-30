// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATileMapSet.h"
#include "Spawner.generated.h"

UCLASS()
class TACTICALGAME_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	TArray<TSubclassOf<class AControllableCharacter>> party;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> Spawns;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnCharacters(bool SnapToGrid);
};
