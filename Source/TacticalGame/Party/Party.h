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
	TMap<int, FCharacterStateArray> Teams2Characters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FCharacterClassArray> Teams2ActorBPClass;

	TMap<int, UFormation*> Team2Formation;

	int SelectedTeam = 0;

public:
	void Init();

	UFUNCTION(BlueprintCallable)
	TArray<UCharacterState*> GetSelectedTeam();

	void HandlePlayerInput();

	UCharacterState* GetCurrentLeader();
};
