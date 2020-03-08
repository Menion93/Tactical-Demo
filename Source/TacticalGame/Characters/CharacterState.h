// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllableCharacter.h"
#include "Characters/Equipment/Bag.h"
#include "CharacterState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UCharacterState : public UObject
{
	GENERATED_BODY()

public:
	UCharacterState();

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY()
	AControllableCharacter* ActorCharacter;

	float CurrentHealth;
	float Health;
	int ActionPoints;
	int CurrentActionPoints;

	// Number of tiles per movement action
	UPROPERTY(EditAnywhere)
	int MovementSpeed = 10;


	UPROPERTY()
	UBag* Bag;

	TSubclassOf<class AControllableCharacter> ActorCharacterClass;

	//UArmorDescriptor* armors;
	
public:
	void Init(FString BPClassName, FName name);

	void ResetActionPoints();

};
