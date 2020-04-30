// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "BattleRangeUtils.generated.h"

class AGCharacter;
/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBattleRangeUtils : public UObject
{
	GENERATED_BODY()

public:

	static bool IsInMeleeRange(AGCharacter* MyCharacter, AGCharacter* Target);
	static bool IsInMeleeRangeFromTile(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target);
	
};
