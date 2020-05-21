// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAttackAction.h"
#include "Items/Equipment/Weapons/RangedWeapon.h"
#include "Grid/Cover.h"
#include "Characters/CharacterState.h"
#include "Characters/GCharacter.h"

void URangedAttackAction::Init(
	ABattleManager* MyBM,
	URangedWeapon* MyWeapon,
	AGCharacter* MyCharacter,
	AGCharacter* MyTarget,
	FTileIndex MyTile)
{
	Super::Init(MyBM, MyWeapon, MyCharacter, MyTarget, MyTile);
	Weapon = MyWeapon;
}

void URangedAttackAction::SortNearestTiles(TArray<FTileIndex>& Array)
{
	AGCharacter* MyChar = Character;
	AGCharacter* MyTarget = Target;

	Array.Sort([MyChar, MyTarget](auto& A, auto& B) {
		FDijkstraNode NodeA = MyChar->PathfindingComponent->ShortestPaths[A];
		FDijkstraNode NodeB = MyChar->PathfindingComponent->ShortestPaths[B];

		if (int(NodeA.Distance) == int(NodeB.Distance))
		{
			FLineOfSight LoSInfoA = MyChar->LoSComponent->GetLoS()[MyTarget->State->Name].Tiles[A];
			return LoSInfoA.CoverType == CoverTypeE::NONE;
		}

		return NodeA.Distance < NodeB.Distance;
	});
}

float URangedAttackAction::GetRoundDamage(int RoundIndex)
{
	if (RoundIndex < 0) return 0;

	float TotalDamage = 0;

	if (RoundIndex < Weapon->AttackSimulation.Rounds.Num())
	{
		FRoundSim RoundSim = Weapon->AttackSimulation.Rounds[RoundIndex];

		for (auto& BulletSim : RoundSim.Round)
		{
			TotalDamage += BulletSim.Damage;
		}
	}

	return TotalDamage;
}
