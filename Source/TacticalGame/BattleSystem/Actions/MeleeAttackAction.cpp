// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackAction.h"
#include "Items/Equipment/Weapons/MeleeWeapon.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
#include "Characters/GCharacter.h"
#include "Characters/CharacterState.h"
#include "Items/Equipment/Equipment.h"

void UMeleeAttackAction::Init(
	ABattleManager* MyBM,
	UMeleeWeapon* MyWeapon,
	AGCharacter* MyCharacter,
	AGCharacter* MyTarget,
	FTileIndex MyTile)
{
	Weapon = MyWeapon;

	Super::MyInit(MyBM, MyWeapon, MyCharacter, MyTarget, MyTile);

	if (Weapon != MyCharacter->State->Equipment->CurrentWeapon)
	{
		MyCharacter->State->Equipment->SwapWeapon();
	}
};


TArray<FTileIndex> UMeleeAttackAction::GetAdjacentTiles(FTileIndex TileIndex)
{
	FTileIndex Up(1, 0);
	FTileIndex Down(-1, 0);
	FTileIndex Left(0, -1);
	FTileIndex Right(0, 1);

	TArray<FTileIndex> Result;

	Result.Add(Up + TileIndex);
	Result.Add(Down + TileIndex);
	Result.Add(Left + TileIndex);
	Result.Add(Right + TileIndex);

	return Result;
}


void UMeleeAttackAction::SortNearestTiles(TArray<FTileIndex>& Array)
{
	Array.Sort([this](auto& A, auto& B) {
		FDijkstraNode NodeA = this->Character->PathfindingComponent->ShortestPaths[A];
		FDijkstraNode NodeB = this->Character->PathfindingComponent->ShortestPaths[B];

		return NodeA.Distance < NodeB.Distance;
	});
}