// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireTeam.h"
#include "./BattleStateMachineStates/BSMState.h"
#include "./BattleStateMachineStates/BSMCharacterInfoState.h"
#include "./BattleStateMachineStates/BSMCharacterSelectedState.h"
#include "./BattleStateMachineStates/BSMDeselectedState.h"
#include "./BattleStateMachineStates/BSMSelectAttackState.h"
#include "./BattleStateMachineStates/BSMSelectEnemyState.h"
#include "./BattleStateMachineStates/BSMSelectAllyState.h"
#include "./BattleStateMachineStates/BSMSelectAllyFromTileState.h"
#include "./BattleStateMachineStates/BSMSelectSupportActionState.h"
#include "./BattleStateMachineStates/BSMSelectEnemyFromTileState.h"
#include "./BattleStateMachineStates/BSMBagState.h"
#include "PlayerFireTeam.generated.h"


UENUM(BlueprintType)
enum class CombatStateE : uint8
{
	DESELECTED_STATE UMETA(DisplayName = "Deselected State"),
	CHARACTER_SELECTED UMETA(DisplayName = "Character Selected"),
	CHARACTER_INFO UMETA(DisplayName = "Character Info"),
	OPEN_BAG UMETA(DisplayName = "Open Bag"),
	SELECT_ATTACK UMETA(DisplayName = "Select Attack"),
	SELECT_ENEMY UMETA(DisplayName = "Select Enemy"),
	SELECT_ENEMY_FROM_TILE UMETA(DisplayName = "Select Enemy From Tile"),
	SELECT_ALLY UMETA(DisplayName = "Select Ally"),
	SELECT_ALLY_FROM_TILE UMETA(DisplayName = "Select Ally From Tile"),
	SELECT_SUPPORT_ACTION UMETA(DisplayName = "Select Support Option"),
};

/**
 * 
 */
UCLASS()
class TACTICALGAME_API APlayerFireTeam : public AFireTeam
{
	GENERATED_BODY()

public:
	APlayerFireTeam();

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
	UBSMSelectEnemyFromTileState* SelectEnemyFromTileState;
	UPROPERTY()
	UBSMSelectAttackState* SelectAttackState;
	UPROPERTY()
	UBSMSelectSupportActionState* SelectSupportActionState;
	UPROPERTY()
	UBSMSelectAllyState* SelectAllyState;
	UPROPERTY()
	UBSMSelectAllyFromTileState* SelectAllyFromTileState;

	int SelectionIndex;

	UPROPERTY()
	TMap<CombatStateE, UBSMState*> StateMachine;

	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> Actionables;

	CombatStateE CurrentState;

	UPROPERTY(EditAnywhere)
	float MoveGridSpeed = 10;

	UPROPERTY(EditAnywhere)
	float DelayToSpeed = 0.25;

private:
	TArray<CombatStateE> StatesHistory;

public:
	void Init_Implementation(ABattleManager* BM) override;
	void OnActionEnd_Implementation() override;
	void OnTurnStart_Implementation() override;
	bool IsTurnEnded_Implementation() override;
	bool IsWinConditionSatisfied_Implementation() override;
	void PlayTurn_Implementation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TransitionToState(CombatStateE State);

	UFUNCTION(BlueprintCallable)
	void TransitionToPrevState();

	virtual void SpawnTeam() override;
	
};
