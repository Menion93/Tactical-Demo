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

	bool FireWeaponDone = false;

public:
	void Init(
		ABattleManager* BM,
		URangedWeapon* MyWeapon,
		AGCharacter* MyCharacter,
		AGCharacter* MyTarget,
		FTileIndex MyTile);

	UFUNCTION(BlueprintCallable)
	void SortNearestTiles(UPARAM(ref) TArray<FTileIndex>& Array);

	UFUNCTION(BlueprintCallable)
	float GetRoundDamage(int RoundIndex);

	UFUNCTION(BlueprintCallable)
	void RoundFinished();
	
};
