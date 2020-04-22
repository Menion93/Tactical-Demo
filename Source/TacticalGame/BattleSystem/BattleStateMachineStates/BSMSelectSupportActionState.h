// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/BattleStateMachineStates/BSMState.h"
#include "BSMSelectSupportActionState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMSelectSupportActionState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMSelectSupportActionState();

public:
	bool InputEventB(float DeltaTime) override;
	void OnEnter() override;
	
};
