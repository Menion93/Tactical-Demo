// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Structs.h"
#include "GridUtils.generated.h"


class AATileMapSet;

USTRUCT(BlueprintType)
struct FDijkstraNode
{
	GENERATED_BODY()

	FTileIndex TileIndex;
	FTileIndex Prev;

	UPROPERTY()
	float Distance;

	FDijkstraNode() {}

	FDijkstraNode(FTileIndex TileParam, FTileIndex PrevNode, float DistanceParam) : TileIndex(TileParam), Prev(PrevNode), Distance(DistanceParam) {}

	bool operator<(const FDijkstraNode &Other) const
	{
		return Distance < Other.Distance;
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
		static void GetShortestPaths(AATileMapSet* TileMap,
			DijkstraOutput &output,
			FTileIndex CurrentTile,
			int PathLenght);

		static TArray<FVectorArray> GetPerimeterPoints(AATileMapSet* TileMap,
			DijkstraOutput &output, 
			int Distance,
			float CellSize, 
			float ZOffset);

		static void UnravelPath(AATileMapSet* TileMap, 
			DijkstraOutput &output,
			FTileIndex Destination,
			TArray<FVector>& Out);

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