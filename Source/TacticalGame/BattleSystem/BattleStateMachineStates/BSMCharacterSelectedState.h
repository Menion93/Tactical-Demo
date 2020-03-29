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


	float MoveTime;
	float DelayToSpeed;

public:
	bool InputEventX() override;
	bool InputEventY() override;
	bool InputEventA() override;
	bool InputEventB() override;

	bool InputEventR2() override;

	bool InputEventLAxis() override;

	void Init(APlayerFireTeam* SM, float MoveGridSpeed, float Delay);

	
private:
	void ResetCooldownMovementGrid();


};
