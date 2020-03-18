// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Structs.h"
#include "GridUtils.generated.h"



USTRUCT()
struct FDijkstraNode
{
	GENERATED_BODY()

	FTile* Tile;

	FTileIndex Prev;

	UPROPERTY()
	float Distance;

	FDijkstraNode() {}

	FDijkstraNode(FTile* TileParam, FTileIndex PrevNode, float DistanceParam) : Tile(TileParam), Prev(PrevNode), Distance(DistanceParam) {}

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

		static TArray<FVectorArray> GetPerimeterPoints(DijkstraOutput &output, int Distance, float CellSize, float ZOffset);

		static void BuildGrid(AActor* Map,
			TMap<FTileIndex, FTile> &TilesMap,
			TArray<UDecalComponent*> &DebugDecals,
			UMaterialInterface* DecalMaterial,
			int Rows,
			int Columns,
			int CellSize,
			bool DrawLinesInEditor);

private:
	static bool AddPerimeterBlock(
		TArray<FVectorArray>& Result,
		TMap<FTileIndex, TArray<FTileIndex>> &Segments,
		TMap<FTileIndex, FVector>& Index2Vec,
		TArray<FTileIndex>& Visited
	);
};