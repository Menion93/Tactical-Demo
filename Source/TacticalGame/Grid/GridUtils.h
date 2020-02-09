// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
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

	FString ToString()
	{
		return FString::Printf(TEXT("%s"), *Tile->ToString());
	}

};

typedef TMap<FTileIndex, FDijkstraNode> DijkstraOutput;

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UGridUtils : public UObject
{
	GENERATED_BODY()

public:
		static void GetShortestPaths(DijkstraOutput &output, FTile* CurrentTile, int PathLenght);

		static TArray<FVector> GetPerimeterPoints(DijkstraOutput &output, int Distance, float CellSize, float ZOffset);

		static void InitStruct(FDijkstraNode &OutNode, FTile* tile, FDijkstraNode* prev, float distance);
	
		static void BuildGrid(AActor* Map,
			TMap<FTileIndex, FTile> &TilesMap,
			TArray<UDecalComponent*> &DebugDecals,
			UMaterialInterface* DecalMaterial,
			int Rows,
			int Columns,
			int CellSize,
			bool DrawLinesInEditor);
};