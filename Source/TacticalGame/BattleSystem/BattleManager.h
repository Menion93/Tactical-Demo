// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AI/BaseEnemyAIController.h"
#include "Characters/CharacterState.h"
#include "Characters/GCharacter.h"
#include "Characters/ControllableCharacter.h"
#include "Utils/GridUtils.h"
#include "./Actions/Action.h"
#include "./BattleStateMachineStates/BSMState.h"
#include "./BattleStateMachineStates/BSMCharacterInfoState.h"
#include "./BattleStateMachineStates/BSMCharacterSelectedState.h"
#include "./BattleStateMachineStates/BSMDeselectedState.h"
#include "./BattleStateMachineStates/BSMSelectAttackState.h"
#include "./BattleStateMachineStates/BSMSelectEnemyState.h"
#include "./BattleStateMachineStates/BSMBagState.h"
#include "Grid/ATileMapSet.h"
#include "BattleManager.generated.h"

class ATacticalGameGameMode;

UENUM(BlueprintType)
enum class CombatStateE : uint8
{
	DESELECTED_STATE UMETA(DisplayName = "Deselected State"),
	CHARACTER_SELECTED UMETA(DisplayName = "Character Selected"),
	CHARACTER_INFO UMETA(DisplayName = "Character Info"),
	OPEN_BAG UMETA(DisplayName = "Open Bag"),
	SELECT_ATTACK UMETA(DisplayName = "Select Attack"),
	SELECT_ENEMY UMETA(DisplayName = "Select Enemy"),
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

	UPROPERTY(BlueprintReadWrite)
	ATacticalGameGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	AATileMapSet* TileMap;

	UPROPERTY(BlueprintReadWrite)
	AControllableCharacter* CurrentCharacter;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* NotAlliedCharacter;

	CombatStateE CurrentState;

	UPROPERTY(BlueprintReadWrite)
	UAction* CurrentAction;

	UPROPERTY()
	TMap<CombatStateE, UBSMState*> StateMachine;

	UPROPERTY()
	AGPlayerController* Input;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex SelectedTile;

	UPROPERTY()
	UBSMDeselectedState* DeselectedState;
	UPROPERTY()
	UBSMCharacterSelectedState* CharacterSelectedState;
	UPROPERTY()
	UBSMCharacterInfoState* CharacterInfoState;
	UPROPERTY()
	UBSMBagState* BagState;
	UPROPERTY()
	UBSMSelectEnemyState* SelectEnemyState;
	UPROPERTY()
	UBSMSelectAttackState* SelectAttackState;

	bool BattleEngaged;

	
public:
	UFUNCTION()
	void ToggleBattleMode(bool mode);

	void TransitionToState(CombatStateE State);

	void PlayTurn();
	void Init();
	void InitBattleState(bool PlayerTurn, bool ForceEngage);
	bool IsTurnEnded();
	bool IsBattleEnded();
	void EndTurn();
	void EndBattle();
	void ResetToPlayerTurn();

	UFUNCTION(BlueprintCallable)
	void SetAction(UAction* Action);

	UFUNCTION(BlueprintCallable)
	FTile GetCurrentTile();
};