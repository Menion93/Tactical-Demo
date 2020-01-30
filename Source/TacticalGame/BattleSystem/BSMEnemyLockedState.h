// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BSMEnemyLockedState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMEnemyLockedState : public UBSMState
{
	GENERATED_BODY()


public:
	UBSMEnemyLockedState();


public:
	virtual UAction* PlayState() override;


};
