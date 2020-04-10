// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCharacter.h"
#include "Characters/Equipment/Equipment.h"
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

	// Default Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// Number of tiles per movement action
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGCharacter> ActorCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UEquipment> EquipmentClass;

public:

	UPROPERTY(BlueprintReadWrite)
		float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ActionPoints;

	UPROPERTY(BlueprintReadWrite)
		int CurrentActionPoints;

	UPROPERTY(BlueprintReadWrite)
		UEquipment* Equipment;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* ActorCharacter;

public:
	void ResetActionPoints();
	void LoadState();

	void LoadDefaultState();

};
