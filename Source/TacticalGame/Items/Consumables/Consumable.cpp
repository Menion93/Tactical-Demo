// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"
#include "Utils/BattleRangeUtils.h"

FString UConsumable::GetMenuDisplayName_Implementation()
{
	return ItemName;
}

bool UConsumable::IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target)
{
	return UBattleRangeUtils::IsInMeleeRange(MyCharacter, Target);
}

bool UConsumable::IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target)
{
	return UBattleRangeUtils::IsInMeleeRangeFromTile(Tile, MyCharacter, Target);;
}

void UConsumable::SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target)
{

}

void UConsumable::ApplyAction_Implementation(AGCharacter* Target)
{

}

UAction* UConsumable::GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile)
{
	return nullptr;
}

ActionType UConsumable::GetActionType_Implementation()
{
	return ActionType::SUPPORT;
}