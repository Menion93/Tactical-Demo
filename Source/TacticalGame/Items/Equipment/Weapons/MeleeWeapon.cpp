// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Grid/Grid.h"
#include "Characters/CharacterState.h"
#include "Utils/BattleRangeUtils.h"
#include "Utils/GridUtils.h"

UMeleeWeapon::UMeleeWeapon()
{

}

bool UMeleeWeapon::IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target)
{
	return UBattleRangeUtils::IsInMeleeRange(MyCharacter, Target);
}

bool UMeleeWeapon::IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	return UBattleRangeUtils::IsInMeleeRangeFromTile(Tile, MyCharacter, Target);;
}

UAction* UMeleeWeapon::GetAction_Implementation()
{
	return nullptr;
}

void UMeleeWeapon::SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target)
{

}

void UMeleeWeapon::ApplyAction_Implementation(AGCharacter* Character)
{

}
