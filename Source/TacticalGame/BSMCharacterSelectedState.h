// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BSMCharacterSelectedState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMCharacterSelectedState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMCharacterSelectedState();

public:
	virtual UAction* PlayState() override;

	
};
