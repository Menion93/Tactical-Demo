// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/BattleStateMachineStates/BSMState.h"
#include "BSMSelectAllyState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMSelectAllyState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMSelectAllyState();

	int AllyIndex;

private:
	AGCharacter* PrevTargetChar;

public:

	bool InputEventA(float DeltaTime) override;
	bool InputEventB(float DeltaTime) override;

	bool InputEventLAxis(float DeltaTime) override;

	void OnEnter() override;

	
};
