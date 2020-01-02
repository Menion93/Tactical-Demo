// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllableCharacter.h"
#include "Bag.h"
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

	float CurrentHealth;
	float Health;
	
	UBag* Bag;
	//UArmorDescriptor* armors;
	
};
