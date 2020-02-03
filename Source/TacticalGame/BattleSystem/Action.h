// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/CharacterState.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UAction : public UObject
{
	GENERATED_BODY()
	
public:
	UAction();

	int ActionPoints;
	UCharacterState* Character;

public:
	bool PlayAction();

};