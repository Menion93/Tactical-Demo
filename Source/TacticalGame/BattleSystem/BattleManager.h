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
class AFireTeam;

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWinConditionSatisfied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterTurnEnded);


UCLASS()
class TACTICALGAME_API ABattleManager : public AActor
{
	GENERATED_BODY()

public:
	ABattleManager();

	UPROPERTY(BlueprintReadWrite)
	ATacticalGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	AGrid* Grid;

	UPROPERTY(BlueprintReadWrite)
	UAction* CurrentAction;

	UPROPERTY(BlueprintReadWrite)
	UAction* GlobalAction;

	UPROPERTY()
	AGPlayerController* Input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AFireTeam*> Teams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFTAlliances> Alliances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAction> GlobalEndTurnActionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAction> GlobalGameEndedClass;

	int TeamIndex;
	int PrevTeamIndex = -1;

private:
	int Turn;

public:
	UPROPERTY(BlueprintAssignable)
	FOnTurnEnded OnTurnEnded;

	UPROPERTY(BlueprintAssignable)
	FOnWinConditionSatisfied OnWinConditionSatisfied;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterTurnEnded OnCharacterTurnEnded;

public:
	void PlayTurn(float DeltaTime);
	void Init();
	void InitBattleState();
	void EndTurn();
	void EndBattle();
	void EndCharacterTurn();

	UFUNCTION(BlueprintCallable)
	int GetTurnNumber();

	UFUNCTION(BlueprintCallable)
	void SetAction(UAction* Action);

	UFUNCTION(BlueprintCallable)
	void SetGlobalAction(UAction* Action);

	UFUNCTION(BlueprintCallable)
	UAction* GetAction();

	UFUNCTION(BlueprintCallable)
	FTile GetSelectedTile();

	UFUNCTION(BlueprintCallable)
	AGCharacter* GetCurrentCharacter();

	UFUNCTION(BlueprintCallable)
	AFireTeam* GetCurrentFireTeam();

	UFUNCTION(BlueprintCallable)
	TArray<AFireTeam*> GetHostileFireTeams(AFireTeam* FireTeam);

	UFUNCTION(BlueprintCallable)
	TArray<AFireTeam*> GetAlliedFireTeams(AFireTeam* FireTeam);

	UFUNCTION(BlueprintCallable)
	bool IsHostile(AFireTeam* FireTeam, AGCharacter* Character);

	UFUNCTION(BlueprintCallable)
	bool IsAlly(AFireTeam* FireTeam, AGCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void RecomputeAllCharactersMetadata();

};
