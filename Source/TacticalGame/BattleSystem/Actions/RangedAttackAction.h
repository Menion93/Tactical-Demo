// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/Actions/ActionableAction.h"
#include "RangedAttackAction.generated.h"

/**
 * 
 */
class URangedWeapon;

UCLASS(Blueprintable)
class TACTICALGAME_API URangedAttackAction : public UActionableAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	URangedWeapon* Weapon;

	UPROPERTY(BlueprintReadWrite)
	bool FireWeaponDone = false;

public:

	void MyInit_Implementation(
		ABattleManager* BM,
		UObject* MyActionable,
		AGCharacter* MyCharacter,
		AGCharacter* MyTarget,
		FTileIndex MyTile) override;

	UFUNCTION(BlueprintCallable)
	void SortNearestTiles(UPARAM(ref) TArray<FTileIndex>& Array);
	
};
