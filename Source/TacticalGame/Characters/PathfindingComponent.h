// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grid/FTile.h"
#include "Utils/GridUtils.h"
#include "Grid/Path.h"
#include "PathfindingComponent.generated.h"

class AGrid;
class AGCharacter;

UCLASS( ClassGroup=(PathfindingComponent), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UPathfindingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathfindingComponent();

	UPROPERTY(BlueprintReadWrite)
	TMap<FTileIndex, FDijkstraNode> ShortestPaths;

	UPROPERTY(BlueprintReadWrite)
	APath* PathActor;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APath> PathClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToleranceBetweetCkpts = 1;

	// Used for pathfinding
	TArray<FVector> MovePoints;

	int PathIndex = -1;


public:	
	UFUNCTION(BlueprintCallable)
	void Init(AGCharacter* MyCharacter);

	UFUNCTION(BlueprintCallable)
	void ShowShortestPath(bool Show);

	UFUNCTION(BlueprintCallable)
	void DrawShortestPath(FTileIndex TileIndex);

	UFUNCTION(BlueprintCallable)
	void ComputeShortestPaths(FTileIndex TileIndex, int DistanceInTilesUnit);

	UFUNCTION(BlueprintCallable)
	bool TileInRange(FTile Tile, int DistanceInTilesUnit);

	UFUNCTION(BlueprintCallable)
	bool MoveTo(FTileIndex TileIndex);
		
};
