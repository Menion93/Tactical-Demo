// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Characters/CharacterState.h"
#include "RangedWeaponActor.h"
#include "Globals/TacticalGameMode.h"

URangedWeapon::URangedWeapon()
{

}


bool URangedWeapon::IsInRange_Implementation(FTileIndex& FromIndex, AGCharacter* MyCharacter, AGCharacter* Target)
{
	if (CurrentAmmo == 0) return false;

	auto LoSData = MyCharacter->LoSComponent->GetLoS();

	FName CharacterName(Target->GetName());
	if (!LoSData.Contains(CharacterName)) return false;

	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	float DistanceFromCharacterTile = 9999999;
	bool Found = false;

	int ActionPoints = Execute_GetActionPoints(this);

	for (auto& Pair : LoSData[CharacterName].Tiles)
	{
		bool NeedsToMove = !(MyCharacter->CurrentTileIndex == Pair.Key);
		bool EnoughActionPoints = MyCharacter->State->CurrentActionPoints >= ActionPoints + int(NeedsToMove);

		// Check if tile is occupied or not
		if (EnoughActionPoints && 
			Pair.Value.Distance <= GetRange() &&
			(GameMode->Grid->GetTile(Pair.Key).Character == nullptr || Pair.Key == MyCharacter->CurrentTileIndex))
		{
			Found = true;

			int NewDistance = MyCharacter->PathfindingComponent->ShortestPaths[Pair.Key].Distance;

			if (DistanceFromCharacterTile > NewDistance)
			{
				FromIndex = Pair.Key;
				DistanceFromCharacterTile = NewDistance;
				auto cover = Pair.Value.CoverType;
			}

		}
	}

	return Found;
}

bool URangedWeapon::IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	FName CharacterName(Target->GetName());

	if (CurrentAmmo == 0) return false;

	if (!MyCharacter->LoSComponent->GetLoS().Contains(CharacterName)) return false;

	if (!MyCharacter->LoSComponent->GetLoS()[CharacterName].Tiles.Contains(Tile.Index)) return false;

	// Check if we have enough action point
	bool NeedsToMove = !(MyCharacter->CurrentTileIndex == Tile.Index);
	bool EnoughActionPoints = MyCharacter->State->CurrentActionPoints >= (Execute_GetActionPoints(this) + int(NeedsToMove));

	return EnoughActionPoints && MyCharacter->LoSComponent->GetLoS()[CharacterName].Tiles[Tile.Index].Distance <= GetRange();
}

void URangedWeapon::SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target)
{
	float Distance = FVector::Distance(Character->GetActorLocation(), Target->GetActorLocation());
	float MyAccuracy = GetAccuracyByRange(Distance);

	float MyBulletDamage = GetBulletDamage();

	float MyCriticalChance = GetCriticalChance();
	float MyCriticalDamage = GetCriticalDamage();

	int CurrentAmmoTemp = CurrentAmmo;

	AttackSimulation = TArray<FRoundSim>();

	for (int i = 0; i < Rounds; i++)
	{
		if (CurrentAmmoTemp < 1) break;

		FRoundSim RoundSim;
		RoundSim.Damage = 0;

		bool RoundHit = false;

		RoundSim.BulletsFired = FMath::Min(CurrentAmmoTemp, BulletsPerRound);

		for (int j = 0; j < RoundSim.BulletsFired; j++)
		{
			int HitProb = FMath::FRand();

			bool BulletHasHit = HitProb < MyAccuracy;
			RoundHit |= BulletHasHit;

			// Has It
			if (BulletHasHit)
			{
				RoundSim.Damage += MyBulletDamage;
			}

			CurrentAmmoTemp--;
		}

		int CritProb = FMath::FRand();
		RoundSim.HasCritted = CritProb < MyCriticalChance;
		RoundSim.Damage = RoundSim.Damage * (1 + MyCriticalDamage * int(RoundSim.HasCritted));

		AttackSimulation.Add(RoundSim);
	}
}

void URangedWeapon::ApplyAction_Implementation(AGCharacter* Character)
{

}

UAction* URangedWeapon::GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile)
{
	URangedAttackAction* CurrentAction = NewObject<URangedAttackAction>(this, ActionClass);
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	CurrentAction->MyInit(GameMode->BattleManager, this, Subject, Target, FromTile);
	return CurrentAction;
}

float URangedWeapon::GetRange()
{
	return Range + BaseRange + RangeRoll;
}

float URangedWeapon::GetBulletDamage()
{
	return BaseBulletDamage + BulletDamage + BulletDamageRoll;
}

float URangedWeapon::GetAccuracyByRange(float Distance)
{
	float MyMaxRange = GetRange();

	if (Distance > MyMaxRange) return 0.1f;

	return AccuracyByRange.GetRichCurve()->Eval(Distance / MyMaxRange, 0);
}

void URangedWeapon::InitWeapon()
{
	CurrentAmmo = MagazineSize;
	CurrentMagazine = Magazine;
}

void URangedWeapon::SpawnWeaponActor(AGCharacter* Character)
{
	RangedWeaponActor = GetWorld()->SpawnActor<ARangedWeaponActor>(WeaponActorClass);
	RangedWeaponActor->Init(this);
	RangedWeaponActor->SnapToActor(Character);
	WeaponActor = RangedWeaponActor;
}

void URangedWeapon::Reload()
{
	if (CurrentMagazine > 0)
	{
		CurrentAmmo = MagazineSize;
		CurrentMagazine--;
	}
}

bool URangedWeapon::CanReload()
{
	return CurrentMagazine > 0 && CurrentAmmo != MagazineSize;
}

bool URangedWeapon::IsRanged()
{
	return true;
}
