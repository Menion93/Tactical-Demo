// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Grid/Grid.h"
#include "Characters/CharacterState.h"
#include "Utils/GridUtils.h"

UMeleeWeapon::UMeleeWeapon()
{
	FTileIndex OffSetU(1, 0);
	FTileIndex OffSetR(0, 1);
	FTileIndex OffSetD(-1, 0);
	FTileIndex OffSetL(0, -1);

	Directions.Add(OffSetU);
	Directions.Add(OffSetD);
	Directions.Add(OffSetR);
	Directions.Add(OffSetL);
}

bool UMeleeWeapon::IsInRange(AGCharacter* MyCharacter, AGCharacter* Target)
{
	TArray<FDijkstraNode> Nodes;
	MyCharacter->ShortestPaths.GenerateValueArray(Nodes);

	Nodes = Nodes.FilterByPredicate([MyCharacter](auto& Node) {
		return Node.Distance <= MyCharacter->State->MovementSpeed;
	});

	for (auto& Node : Nodes)
	{
		if (IsInRangeFromTile(MyCharacter->Grid->GetTile(Node.TileIndex), Target))
		{
			return true;
		}
	}

	return false;
}

bool UMeleeWeapon::IsInRangeFromCurrentPosition(AGCharacter* MyCharacter, AGCharacter* Target)
{
	FTile Tile = MyCharacter->Grid->GetTile(MyCharacter->CurrentTileIndex);
	return IsInRangeFromTile(Tile, Target);
}

bool UMeleeWeapon::IsInRangeFromTile(FTile Tile, AGCharacter* Target)
{
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

bool UMeleeWeapon::CanAttackEnemy_Implementation(AGCharacter* Character, AGCharacter* Target)
{
	return IsInRange(Character, Target);
}


void UMeleeWeapon::SimulateAttack(AGCharacter* Character, AGCharacter* Target)
{

}

void UMeleeWeapon::ApplyAttack(AGCharacter* Character)
{

}
