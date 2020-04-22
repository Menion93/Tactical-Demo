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

	int TeamIndex;
	int PrevTeamIndex = -1;

public:
	void PlayTurn(float DeltaTime);
	void Init();
	void InitBattleState();
	void EndTurn();
	void EndBattle();

	UFUNCTION(BlueprintCallable)
	void SetAction(UAction* Action);

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


};
