// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Grid/Grid.h"
#include "Characters/CharacterState.h"
#include "Globals/TacticalGameMode.h"
#include "Utils/BattleRangeUtils.h"
#include "Utils/GridUtils.h"
#include "MeleeWeaponActor.h"


UMeleeWeapon::UMeleeWeapon()
{

}

bool UMeleeWeapon::IsInRange_Implementation(FTileIndex& FromIndex, AGCharacter* MyCharacter, AGCharacter* Target)
{
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());

	return UBattleRangeUtils::IsInMeleeRange(GameMode->Grid, FromIndex, MyCharacter, Target, Execute_GetActionPoints(this));
}

bool UMeleeWeapon::IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	return UBattleRangeUtils::IsInMeleeRangeFromTile( Tile, MyCharacter, Target, Execute_GetActionPoints(this));
}

UAction* UMeleeWeapon::GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile)
{
	UMeleeAttackAction* MyCurrentAction = NewObject<UMeleeAttackAction>(this, ActionClass);
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	MyCurrentAction->MyInit(GameMode->BattleManager, this, Subject, Target, FromTile);
	return MyCurrentAction;
}

void UMeleeWeapon::SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target)
{
	float Distance = FVector::Distance(Character->GetActorLocation(), Target->GetActorLocation());
	float MyAccuracy = GetAccuracy();

	float MyDamage = GetDamage();

	float MyCriticalChance = GetCriticalChance();
	float MyCriticalDamage = GetCriticalDamage();

	AttackSimulation = TArray<FRoundSim>();

	for (int i = 0; i < AttacksPerTurn; i++)
	{
		FRoundSim Attack;

		int HitProb = FMath::FRand();

		Attack.HasHit = HitProb < MyAccuracy;

		// Has It
		if (Attack.HasHit)
		{
			int CritProb = FMath::FRand();

			Attack.HasCritted = CritProb < MyCriticalChance;
			Attack.Damage = MyDamage * (1 + MyCriticalDamage * int(Attack.HasCritted));
		}

		AttackSimulation.Add(Attack);
	}
}

void UMeleeWeapon::ApplyAction_Implementation(AGCharacter* Character)
{

}

float UMeleeWeapon::GetAccuracy()
{
	return BaseAccuracy + Accuracy + AccuracyRoll;
}

float UMeleeWeapon::GetDamage()
{
	return BaseDamage + Damage + DamageRoll;
}

void UMeleeWeapon::InitWeapon()
{

}


void UMeleeWeapon::SpawnWeaponActor(AGCharacter* Character)
{
	MeleeWeaponActor = GetWorld()->SpawnActor<AMeleeWeaponActor>(WeaponActorClass);
	MeleeWeaponActor->Init(this);
	MeleeWeaponActor->SnapToActor(Character);
	WeaponActor = MeleeWeaponActor;
}

bool UMeleeWeapon::IsRanged()
{
	return false;
}


