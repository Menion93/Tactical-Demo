// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/GCharacter.h"
#include "Grid/FTile.h"
#include "FireTeam.generated.h"

//class AGCharacter;
class ABattleManager;
/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API AFireTeam : public AActor
{
	GENERATED_BODY()

public:
	AFireTeam();

	// Can Set Actors Spawned directly from blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AGCharacter*> Characters;

	// You can spawn on runtime providing spawn points and character classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UCharacterState>> CharacterClasses;

	UPROPERTY(BlueprintReadWrite)
	ABattleManager* BattleManager;

	UPROPERTY()
	USceneComponent* RootComp;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* CurrentCharacter;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* TargetCharacter;

	UPROPERTY(BlueprintReadWrite)
	TArray<AGCharacter*> Targets;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex SelectedTile;



public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init(ABattleManager* BM);
	virtual void Init_Implementation(ABattleManager* BM);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnActionEnd();
	virtual void OnActionEnd_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnTurnStart();
	virtual void OnTurnStart_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsTurnEnded();
	virtual bool IsTurnEnded_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsWinConditionSatisfied();
	virtual bool IsWinConditionSatisfied_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayTurn(float DeltaTime);
	virtual void PlayTurn_Implementation(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	bool InFireTeam(AGCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void SetFireTeam(TArray<AGCharacter*> FireTeam);

	UFUNCTION(BlueprintCallable)
	virtual void SpawnTeam();

	UFUNCTION(BlueprintCallable)
	void RecomputeAllCharactersMetadata();
	
};
