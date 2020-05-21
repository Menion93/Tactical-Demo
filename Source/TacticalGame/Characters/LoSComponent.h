// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grid/FTile.h"
#include "Utils/GridUtils.h"
#include "Utils/Structs.h"
#include "LoSComponent.generated.h"

class AGCharacter;

UCLASS( ClassGroup=(LoSComponent), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API ULoSComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULoSComponent();

	// Line of Sights Computations
	UPROPERTY(BlueprintReadWrite)
	TMap<FName, FLineOfSights> LoS;

public:

	UFUNCTION(BlueprintCallable)
	void ComputeLoS(TMap<FTileIndex, FDijkstraNode>& ShortestPaths, AGCharacter* Subject);

	UFUNCTION(BlueprintCallable)
	TMap<FName, FLineOfSights> GetLoS();

private:
	void AddLoS(
		AGCharacter* Character,
		FTile& Tile,
		CoverTypeE Cover,
		float Distance);
};
