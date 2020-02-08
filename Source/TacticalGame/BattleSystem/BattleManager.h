// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AI/BaseEnemyAIController.h"
#include "Characters/CharacterState.h"
#include "Characters/ControllableCharacter.h"
#include "Grid/GridUtils.h"
#include "./BattleStateMachineStates/BSMState.h"
#include "./BattleStateMachineStates/BSMEnemyLockedState.h"
#include "./BattleStateMachineStates/BSMCharacterSelectedState.h"
#include "./BattleStateMachineStates/BSMDeselectedState.h"
#include "./BattleStateMachineStates/BSMTileSelectedState.h"
#include "BattleManager.generated.h"

class ATacticalGameGameMode;

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
class TACTICALGAME_API UBattleManager : public UObject
{
	GENERATED_BODY()

public:
	UBattleManager();

	bool PlayerTurn;

	ATacticalGameGameMode* GameMode;
	AControllableCharacter* CurrentCharacter;

	CombatStateE CurrentState;


	UPROPERTY()
	TMap<CombatStateE, UBSMState*> StateMachine;

	AGPlayerController* Input;

	AATileMapSet* TileMap;
	FTile* SelectedTile;

	DECLARE_DELEGATE(Action)
	Action CurrentAction = nullptr;

	bool HasActionEnded = true;

	UPROPERTY()
	UBSMDeselectedState* DeselectedState;

	UPROPERTY()
	UBSMCharacterSelectedState* CharacterSelectedState;

	UPROPERTY()
	UBSMEnemyLockedState* EnemyLockedState;

	UPROPERTY()
	UBSMTileSelectedState* TileSelectedState;
	
public:
	UFUNCTION()
	void ToggleBattleMode(bool mode);

	void PlayTurn();
	void Init();
	void InitBattleState(bool PlayerTurn);
	bool IsTurnEnded();
	bool IsBattleEnded();
	void EndTurn();
	void EndBattle();
	void ResetToPlayerTurn();
	void EndCurrentAction();
	Action GetActionDelegate();
};