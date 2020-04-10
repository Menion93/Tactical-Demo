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
	UBSMSelectAttackState* SelectAttackState;

	int SelectionIndex;

	UPROPERTY()
	TMap<CombatStateE, UBSMState*> StateMachine;

	CombatStateE CurrentState;
	CombatStateE PrevState;

	UPROPERTY(EditAnywhere)
	float MoveGridSpeed = 10;

	UPROPERTY(EditAnywhere)
	float DelayToSpeed = 0.25;


public:
	void Init_Implementation(ABattleManager* BM) override;
	void OnActionEnd_Implementation() override;
	void OnTurnStart_Implementation() override;
	bool IsTurnEnded_Implementation() override;
	bool IsWinConditionSatisfied_Implementation() override;
	void PlayTurn_Implementation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TransitionToState(CombatStateE State);

	virtual void SpawnTeam() override;
	
};
