// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCharacter.h"
#include "Characters/Equipment/Bag.h"
#include "CharacterState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TACTICALGAME_API UCharacterState : public UObject
{
	GENERATED_BODY()

public:
	UCharacterState();

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY()
	AGCharacter* ActorCharacter;

	UPROPERTY(BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ActionPoints;

	UPROPERTY(BlueprintReadWrite)
	int CurrentActionPoints;

	// Number of tiles per movement action
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MovementSpeed;

	UPROPERTY(BlueprintReadWrite)
	UBag* Bag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGCharacter> ActorCharacterClass;

	//UArmorDescriptor* armors;
	
public:
	void ResetActionPoints();
	void LoadState();

};
