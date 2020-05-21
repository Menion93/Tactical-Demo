// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleRangeUtils.h"
#include "Characters/GCharacter.h"
#include "Characters/CharacterState.h"
#include "Grid/Grid.h"


bool UBattleRangeUtils::IsInMeleeRange(AGCharacter* MyCharacter, AGCharacter* Target)
{
	TArray<FDijkstraNode> Nodes;
	MyCharacter->PathfindingComponent->ShortestPaths.GenerateValueArray(Nodes);

	Nodes = Nodes.FilterByPredicate([MyCharacter](auto& Node) {
		return int(Node.Distance) <= MyCharacter->State->MovementSpeed;
	});

	for (auto& Node : Nodes)
	{
		if (IsInMeleeRangeFromTile(MyCharacter->Grid->GetTile(Node.TileIndex), MyCharacter, Target))
		{
			return true;
		}
	}

	return false;
}

bool UBattleRangeUtils::IsInMeleeRangeFromTile(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	FTileIndex OffSetU(1, 0);
	FTileIndex OffSetR(0, 1);
	FTileIndex OffSetD(-1, 0);
	FTileIndex OffSetL(0, -1);

	TArray<FTileIndex> Directions;
	Directions.Add(OffSetU);
	Directions.Add(OffSetD);
	Directions.Add(OffSetR);
	Directions.Add(OffSetL);

	bool InRange = false;
	for (auto& Direction : Directions)
	{
		if (Tile.Direction2Neighbours.Contains(Direction))
		{
			InRange |= Tile.Direction2Neighbours[Direction].Key->Character == Target;
		}
	}

	return InRange;
}