// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BSMState.h"
#include "Characters/GCharacter.h"
#include "Grid/FTile.h"
#include "BSMCharacterSelectedState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMCharacterSelectedState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMCharacterSelectedState();

	bool CooldownMovementGrid;
	FTimerHandle timerHandle;
	bool AxisReleased;
	float time;

public:
	void InputEventX() override;
	void InputEventY() override;
	void InputEventA() override;
	void InputEventB() override;

	void InputEventR2() override;

	void InputEventLAxis() override;

	
private:
	void ResetCooldownMovementGrid();


};
