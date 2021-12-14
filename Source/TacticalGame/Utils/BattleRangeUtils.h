// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Grid/Grid.h"
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

	static bool IsInMeleeRange(AGrid* Grid, FTileIndex& FromTileIndex, AGCharacter* MyCharacter, AGCharacter* Target, int ActionPoints);
	static bool IsInMeleeRangeFromTile(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target, int ActionPoints);
	
};
