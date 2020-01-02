// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FTile.h"
#include "GridUtils.generated.h"



USTRUCT()
struct FDijkstraNode
{
	GENERATED_BODY()

	FTile* Tile;

	FDijkstraNode* Prev;

	UPROPERTY()
		float Distance;

	bool operator<(const FDijkstraNode &Other) const
	{
		return Distance < Other.Distance;
	}

};

typedef TMap<FVector2D, FDijkstraNode*> DijkstraOutput;

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UGridUtils : public UObject
{
	GENERATED_BODY()

public:
		static DijkstraOutput GetShortestPaths(FTile* CurrentTile, int PathLenght);

		static TArray<FVector> GetPerimeterAtDistance(TArray<FDijkstraNode*> Nodes, int Distance);

		static void InitStruct(FDijkstraNode &OutNode, FTile* tile, FDijkstraNode* prev, float distance);
	
};