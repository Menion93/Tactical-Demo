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

	AttackSimulation = FRangedWeaponSim();

	for (int i = 0; i < Rounds; i++)
	{
		FRoundSim RoundSim;

		for (int j = 0; j < BulletsPerRound; j++)
		{
			FBulletSim BulletSim;

			int HitProb = FMath::FRand();

			BulletSim.HasHit = HitProb < MyAccuracy;

			// Has It
			if (BulletSim.HasHit)
			{
				int CritProb = FMath::FRand();

				BulletSim.HasCritted = CritProb < MyCriticalChance;
				BulletSim.Damage = MyBulletDamage * (1 + MyCriticalDamage * int(BulletSim.HasCritted));
			}
			RoundSim.Round.Add(BulletSim);
		}
		AttackSimulation.Rounds.Add(RoundSim);
	}
}

void URangedWeapon::ApplyAction_Implementation(AGCharacter* Character)
{

}

UAction* URangedWeapon::GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile)
{
	URangedAttackAction* Action = NewObject<URangedAttackAction>(this, ActionClass);
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	Action->Init(GameMode->BattleManager, this, Subject, Target, FromTile);
	return Action;
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

	if (Distance > Range) return 0;

	return AccuracyByRange.GetRichCurve()->Eval(Distance / MyMaxRange, 0);
}

void URangedWeapon::InitWeapon()
{
	CurrentAmmo = MagazineSize;
}