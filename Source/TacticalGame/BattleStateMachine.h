// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "GPlayerController.h"
#include "ATileMapSet.h"
#include "BattleStateMachine.generated.h"

typedef UAction* (UBattleStateMachine::*StateMachineFunc)(void);

UENUM(BlueprintType)
enum class CombatStateE : uint8
{
	DESELECTED_STATE UMETA(DisplayName = "Deselected State"),
	CHARACTER_SELECTED UMETA(DisplayName = "Character Selected"),
	ENEMY_LOCKED UMETA(DisplayName = "Enemy Locked"),
	TILE_SELECTED UMETA(DisplayName = "Tile Selected"),

};

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBattleStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UBattleStateMachine();

	TMap<CombatStateE, StateMachineFunc> State2Method;

	AGPlayerController* Input;
	AATileMapSet* TileMap;


public:
	UAction* PlayState();
	void Reset();
	void Init();


private:
	CombatStateE CurrentState;

	UAction* DeselectedState();
	UAction* CharacterSelected();
	UAction* EnemyLocked();
	UAction* TileSelected();
	
};
