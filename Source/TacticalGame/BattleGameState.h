// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseEnemyAIController.h"
#include "CharacterState.h"
#include "GridUtils.h"
#include "Action.h"
#include "BattleStateMachine.h"
#include "BattleGameState.generated.h"



/**
 * 
 */
UCLASS()
class TACTICALGAME_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	bool GridEnabled;
	bool PlayerTurn;
	int CurrentCharacter;
	CombatStateE CurrentState;

	TMap<UCharacterState*, DijkstraOutput> Player2Paths;
	TMap<UCharacterState*, bool> Player2Turn;

	UAction* CurrentAction;
	
	UBattleStateMachine* StateMachine;

public:
	ABattleGameState();

	UFUNCTION()
		void ToggleBattleMode(bool mode);

	void PlayTurn();
	void Init();
	void InitBattleState(bool PlayerTurn);
	bool IsTurnEnded();
	bool IsBattleEnded();
	void EndTurn();
	void EndBattle();

};