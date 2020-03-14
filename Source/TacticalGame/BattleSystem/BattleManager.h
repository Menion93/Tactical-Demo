// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AI/BaseEnemyAIController.h"
#include "Characters/CharacterState.h"
#include "Characters/GCharacter.h"
#include "Characters/ControllableCharacter.h"
#include "Utils/GridUtils.h"
#include "./BattleStateMachineStates/BSMState.h"
#include "./BattleStateMachineStates/BSMCharacterInfoState.h"
#include "./BattleStateMachineStates/BSMCharacterSelectedState.h"
#include "./BattleStateMachineStates/BSMDeselectedState.h"
#include "BattleManager.generated.h"

class ATacticalGameGameMode;

UENUM(BlueprintType)
enum class CombatStateE : uint8
{
	DESELECTED_STATE UMETA(DisplayName = "Deselected State"),
	CHARACTER_SELECTED UMETA(DisplayName = "Character Selected"),
	CHARACTER_INFO UMETA(DisplayName = "Character Info"),
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

	UPROPERTY(BlueprintReadWrite)
	AControllableCharacter* CurrentCharacter;

	UPROPERTY()
	AGCharacter* NotAlliedCharacter;

	CombatStateE CurrentState;


	UPROPERTY()
	TMap<CombatStateE, UBSMState*> StateMachine;

	AGPlayerController* Input;

	FTile* SelectedTile;

	DECLARE_DELEGATE(Action)
	Action CurrentAction = nullptr;

	bool HasActionEnded = true;

	UPROPERTY()
	UBSMDeselectedState* DeselectedState;

	UPROPERTY()
	UBSMCharacterSelectedState* CharacterSelectedState;

	UPROPERTY()
	UBSMCharacterInfoState* CharacterInfoState;

	UPROPERTY()
	bool BattleEngaged;
	
public:
	UFUNCTION()
	void ToggleBattleMode(bool mode);

	void PlayTurn();
	void Init();
	void InitBattleState(bool PlayerTurn, bool ForceEngage);
	bool IsTurnEnded();
	bool IsBattleEnded();
	void EndTurn();
	void EndBattle();
	void ResetToPlayerTurn();
	void EndCurrentAction();
	Action GetActionDelegate();
};