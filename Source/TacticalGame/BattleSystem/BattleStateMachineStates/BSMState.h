// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Engine/World.h"
#include "Grid/ATileMapSet.h"
#include "Globals/GPlayerController.h"
#include "BSMState.generated.h"


class UBattleManager;

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMState : public UObject
{
	GENERATED_BODY()
	
public:
	UBSMState();

protected:
	UBattleManager* BattleManager;
	AGPlayerController* Input;
	AATileMapSet* TileMap;

public:
	virtual void Init();

	virtual void PlayState();	
};
