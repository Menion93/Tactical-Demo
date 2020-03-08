// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BSMState.h"
#include "BSMNpcSelectedState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMNpcSelectedState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMNpcSelectedState();

	bool CooldownMovementGrid;
	FTimerHandle timerHandle;
	bool AxisReleased;
	float time;

public:
	virtual void PlayState() override;

private:
	void ResetCooldownMovementGrid();

	
};
