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

void UWeaponCore::SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target)
{

}

void UWeaponCore::ApplyAction_Implementation(AGCharacter* Target)
{

}

UAction* UWeaponCore::GetAction_Implementation()
{
	return nullptr;
}

FString UWeaponCore::GetMenuDisplayName_Implementation()
{
	return WeaponName;
}

ActionType UWeaponCore::GetActionType_Implementation()
{
	return ActionType::OFFENSIVE;
}