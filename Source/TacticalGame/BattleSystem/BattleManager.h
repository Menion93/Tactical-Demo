// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Characters/CharacterState.h"
#include "Characters/GCharacter.h"
#include "Utils/GridUtils.h"
#include "./Actions/Action.h"
#include "Grid/Grid.h"
#include "FireTeam.h"
#include "BattleManager.generated.h"

class ATacticalGameMode;


/**
 * 
 */
UCLASS()
class TACTICALGAME_API ABattleManager : public AActor
{
	GENERATED_BODY()

public:
	ABattleManager();

	bool PlayerTurn;

	UPROPERTY(BlueprintReadWrite)
	ATacticalGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	AGrid* Grid;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* CurrentCharacter;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* NotAlliedCharacter;

	UPROPERTY(BlueprintReadWrite)
	UAction* CurrentAction;

	UPROPERTY(BlueprintReadWrite)
	UAction* GlobalAction;

	UPROPERTY()
	AGPlayerController* Input;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex SelectedTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AFireTeam*> Teams;

	int TeamIndex;
	int PrevTeamIndex = -1;

public:
	void PlayTurn();
	void Init();
	void InitBattleState(bool PlayerTurn, bool ForceEngage);
	void EndTurn();
	void EndBattle();

	UFUNCTION(BlueprintCallable)
	void SetAction(UAction* Action);

	UFUNCTION(BlueprintCallable)
	FTile GetCurrentTile();

	UFUNCTION(BlueprintCallable)
	AFireTeam* GetPlayerFireTeam();
};