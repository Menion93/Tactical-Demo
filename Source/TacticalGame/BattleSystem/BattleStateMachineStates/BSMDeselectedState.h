// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BSMState.h"
#include "BSMDeselectedState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMDeselectedState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMDeselectedState();

	bool CooldownMovementGrid;
	FTimerHandle timerHandle;
	bool AxisReleased;
	float time;

public:
	void InputEventX() override;
	void InputEventY() override;
	void InputEventA() override;
	void InputEventB() override;

	void InputEventLAxis() override;

	virtual void InputEventR1();
	virtual void InputEventL1();



private:
	void ResetCooldownMovementGrid();

};