// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/CharacterState.h"
#include "Formation.h"
#include "Utils/Structs.h"
#include "Party.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UParty : public UObject
{
	GENERATED_BODY()

public:
	UParty();

	// Each team can contain up to 3 members + 1 leader
	// First elem is always the leader
	// Member of the team follow the leader movement
	UPROPERTY(BlueprintReadWrite)
	TArray<UCharacterState*> Characters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UCharacterState>> CharactersClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> TeamIndexes;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCharacterState*> Team;


public:
	void Init();

	UFUNCTION(BlueprintCallable)
	TArray<UCharacterState*> GetTeam();

	void HandlePlayerInput();

	UCharacterState* GetCurrentLeader();
};
