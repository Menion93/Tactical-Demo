// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BSMTileSelectedState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMTileSelectedState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMTileSelectedState();

public:
	virtual void PlayState() override;

	
};
