// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Characters/CharacterState.h"

URangedWeapon::URangedWeapon()
{

}

bool URangedWeapon::IsInRange(AGCharacter* MyCharacter, AGCharacter* Target)
{
	if (!MyCharacter->LoS.Contains(Target->State->Name)) return false;

	for (auto& Pair : Target->LoS[Target->State->Name].Tiles)
	{
		if (Pair.Value.Distance < GetRange())
		{
			return true;
		}
	}

	return false;
}

bool URangedWeapon::IsInRangeFromCurrentPosition(AGCharacter* MyCharacter, AGCharacter* Target)
{
	if (!MyCharacter->LoS.Contains(Target->State->Name)) return false;

	if(!Target->LoS[Target->State->Name].Tiles.Contains(MyCharacter->CurrentTileIndex)) return false;

	return Target->LoS[Target->State->Name].Tiles[MyCharacter->CurrentTileIndex].Distance < GetRange();
}

bool URangedWeapon::CanAttackEnemy_Implementation(AGCharacter* Character, AGCharacter* Target)
{
	return IsInRange(Character, Target);
}

void URangedWeapon::SimulateAttack(AGCharacter* Character, AGCharacter* Target)
{

}

void URangedWeapon::ApplyAttack(AGCharacter* Character)
{

}

float URangedWeapon::GetRange()
{
	return 0;
}

