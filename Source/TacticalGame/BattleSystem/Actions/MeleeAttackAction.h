// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/Actions/ActionableAction.h"
#include "MeleeAttackAction.generated.h"

/**
 * 
 */
class UMeleeWeapon;

UCLASS(Blueprintable)
class TACTICALGAME_API UMeleeAttackAction : public UActionableAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UMeleeWeapon* Weapon;

public:
	void Init(
		ABattleManager* BM,
		UMeleeWeapon* MyWeapon,
		AGCharacter* MyCharacter,
		AGCharacter* MyTarget,
		FTileIndex MyTile);

	UFUNCTION(BlueprintCallable)
	TArray<FTileIndex> GetAdjacentTiles(FTileIndex TileIndex);

	UFUNCTION(BlueprintCallable)
	void SortNearestTiles(UPARAM(ref) TArray<FTileIndex>& Array);

};
