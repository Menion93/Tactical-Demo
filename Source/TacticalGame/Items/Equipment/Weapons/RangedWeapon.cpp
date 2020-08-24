// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Characters/CharacterState.h"
#include "RangedWeaponActor.h"
#include "Globals/TacticalGameMode.h"

URangedWeapon::URangedWeapon()
{

}


bool URangedWeapon::IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target)
{
	if (CurrentAmmo == 0) return false;

	auto LoSData = MyCharacter->LoSComponent->GetLoS();

	if (!LoSData.Contains(Target->State->Name)) return false;

	for (auto& Pair : LoSData[Target->State->Name].Tiles)
	{
		if (Pair.Value.Distance <= GetRange())
		{
			return true;
		}
	}

	return false;
}

bool URangedWeapon::IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	if (CurrentAmmo == 0) return false;

	if (!MyCharacter->LoSComponent->GetLoS().Contains(Target->State->Name)) return false;

	if (!MyCharacter->LoSComponent->GetLoS()[Target->State->Name].Tiles.Contains(Tile.Index)) return false;

	return MyCharacter->LoSComponent->GetLoS()[Target->State->Name].Tiles[Tile.Index].Distance <= GetRange();
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
	CurrentAction = NewObject<URangedAttackAction>(this, ActionClass);
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	CurrentAction->Init(GameMode->BattleManager, this, Subject, Target, FromTile);
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

	if (Distance > MyMaxRange) return 0;

	return AccuracyByRange.GetRichCurve()->Eval(Distance / MyMaxRange, 0);
}

void URangedWeapon::InitWeapon()
{
	CurrentAmmo = MagazineSize;
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
	CurrentAmmo = MagazineSize;
}
