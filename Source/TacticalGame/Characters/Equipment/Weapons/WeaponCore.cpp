// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCore.h"


// Sets default values for this component's properties
UWeaponCore::UWeaponCore()
{

}

bool UWeaponCore::IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target)
{
	return false;
}

bool UWeaponCore::IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	return false;
}

void UWeaponCore::SimulateAttack_Implementation(AGCharacter* Character, AGCharacter* Target)
{

}

void UWeaponCore::ApplyAttack_Implementation(AGCharacter* Target)
{

}

void UWeaponCore::Attack_Implementation(AGCharacter* Character, AGCharacter* Target)
{
	SimulateAttack(Character, Target);
	ApplyAttack(Target);
}

FString UWeaponCore::GetName_Implementation()
{
	return WeaponName;
}