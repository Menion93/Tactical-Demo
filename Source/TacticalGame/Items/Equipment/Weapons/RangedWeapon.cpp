// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Characters/CharacterState.h"

URangedWeapon::URangedWeapon()
{

}

bool URangedWeapon::IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target)
{
	if (!MyCharacter->LoS.Contains(Target->State->Name)) return false;

	for (auto& Pair : MyCharacter->LoS[Target->State->Name].Tiles)
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
	if (!MyCharacter->LoS.Contains(Target->State->Name)) return false;

	if(!MyCharacter->LoS[Target->State->Name].Tiles.Contains(Tile.Index)) return false;

	return MyCharacter->LoS[Target->State->Name].Tiles[Tile.Index].Distance <= GetRange();
}

void URangedWeapon::SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target)
{

}

void URangedWeapon::ApplyAction_Implementation(AGCharacter* Character)
{

}

UAction* URangedWeapon::GetAction_Implementation()
{
	return nullptr;
}


float URangedWeapon::GetRange()
{
	return Range + BaseRange;
}