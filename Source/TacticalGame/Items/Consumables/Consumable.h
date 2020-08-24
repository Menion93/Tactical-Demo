// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "BattleSystem/Actions/Actionable.h"
#include "Consumable.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UConsumable : public UItem, public IActionable
{
	GENERATED_BODY()
	
public:

	virtual FString GetMenuDisplayName_Implementation() override;

	virtual bool IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target);
	virtual bool IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target);
	virtual int GetActionPoints_Implementation();

	virtual void SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target);
	virtual void ApplyAction_Implementation(AGCharacter* Target);

	virtual UAction* GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile);

	virtual ActionType GetActionType_Implementation();
};
