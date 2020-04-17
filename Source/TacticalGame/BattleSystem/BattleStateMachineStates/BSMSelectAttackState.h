// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BSMSelectAttackState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMSelectAttackState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMSelectAttackState();

public:
	bool InputEventB(float DeltaTime) override;
	void OnEnter() override;
};
