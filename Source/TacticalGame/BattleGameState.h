// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseEnemyAIController.h"
#include "CharacterState.h"
#include "GridUtils.h"
#include "BattleGameState.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class Turn : uint8
{
	TE_Player 	UMETA(DisplayName = "Player"),
	TE_Enemy 	UMETA(DisplayName = "Enemy"),
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
	Turn CurrentTurn;
	int CurrentCharacter;


	TMap<UCharacterState*, DijkstraOutput> player2paths;


public:
	ABattleGameState();

	UFUNCTION()
		void ToggleBattleMode(bool mode);

	void PlayTurn();
	void InitBattleState(Turn FirstTurn);
	
};