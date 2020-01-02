// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseEnemyAIController.h"
#include "CharacterState.h"
#include "GridUtils.h"
#include "BattleGameState.generated.h"

UENUM(BlueprintType)
enum class CombatStateE : uint8
{
	CSE_CHAR_DESELECTED UMETA(DisplayName = "PlayerDeselected"),
	CSE_CHAR_SELECTED UMETA(DisplayName = "PlayerSelected"),
	CSE_BAG UMETA(DisplayName = "Bag"),
	CSE_ENEMY_TURN UMETA(DisplayName = "EnemyTurn"),
	
};


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

	TMap<UCharacterState*, DijkstraOutput> player2paths;
	TMap<UCharacterState*, bool> player2turn;


public:
	ABattleGameState();

	UFUNCTION()
		void ToggleBattleMode(bool mode);

	void PlayTurn();
	void InitBattleState(bool PlayerTurn);
	void EndTurn();
	bool IsTurnEnded();
	bool IsBattleEnded();
	
};