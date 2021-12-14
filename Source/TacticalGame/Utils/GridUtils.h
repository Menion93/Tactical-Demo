// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Structs.h"
#include "GridUtils.generated.h"


class AGrid;

USTRUCT(BlueprintType)
struct FDijkstraNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FTileIndex TileIndex;

	UPROPERTY(BlueprintReadOnly)
	FTileIndex Prev;

	UPROPERTY(BlueprintReadOnly)
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
		static void GetShortestPaths(AGrid* Grid,
			DijkstraOutput &output,
			FTileIndex CurrentTile,
			int PathLenght,
			bool IgnoreCharacter);

		static TArray<FVectorArray> GetPerimeterPoints(AGrid* Grid,
			TArray<FTileIndex> CharacterPositions,
			DijkstraOutput& outputIgnoreChar,
			DijkstraOutput &output,
			int Distance,
			float CellSize,
			float ZOffset);

		static void UnravelPath(AGrid* Grid,
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