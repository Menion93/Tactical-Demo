// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BSMBagState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMBagState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMBagState();

public:
	void InputEventB() override;

	void OnEnter() override;
};
