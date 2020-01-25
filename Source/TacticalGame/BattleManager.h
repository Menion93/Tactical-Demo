// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseEnemyAIController.h"
#include "CharacterState.h"
#include "ControllableCharacter.h"
#include "GridUtils.h"
#include "Action.h"
#include "BSMState.h"
#include "BSMEnemyLockedState.h"
#include "BSMCharacterSelectedState.h"
#include "BSMDeselectedState.h"
#include "BSMTileSelectedState.h"
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

	bool GridEnabled;
	bool PlayerTurn;

	ATacticalGameGameMode* GameMode;
	AControllableCharacter* CurrentCharacter;

	CombatStateE CurrentState;

	TMap<FName, DijkstraOutput> Player2Paths;
	TMap<FName, bool> Player2Turn;

	UPROPERTY()
	TMap<CombatStateE, UBSMState*> StateMachine;

	AGPlayerController* Input;

	AATileMapSet* TileMap;
	FTile* SelectedTile;

	UPROPERTY()
	UAction* CurrentAction = nullptr;

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
	void ResetStateMachine();
};