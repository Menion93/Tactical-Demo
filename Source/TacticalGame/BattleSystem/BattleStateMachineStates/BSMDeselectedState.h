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

	float MoveTime;
	float DelayToSpeed;

public:
	bool InputEventX() override;
	bool InputEventY() override;
	bool InputEventA() override;
	bool InputEventB() override;

	bool InputEventLAxis() override;

	virtual bool InputEventR1();
	virtual bool InputEventL1();

	void Init(APlayerFireTeam* SM, float MoveGridSpeed, float Delay);


private:
	void ResetCooldownMovementGrid();

};