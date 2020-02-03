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
	virtual UAction* PlayState() override;
	//virtual void Init() override;

private:
	void ResetCooldownMovementGrid();

};