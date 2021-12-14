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

	bool CoolDownYawRotation;

public:
	bool InputEventY(float DeltaTime) override;
	bool InputEventA(float DeltaTime) override;
	bool InputEventB(float DeltaTime) override;

	bool InputEventR2(float DeltaTime) override;

	bool InputEventLAxis(float DeltaTime) override;
	bool InputEventRAxis(float DeltaTime) override;

	void InitState(APlayerFireTeam* SM, float MoveGridSpeed, float Delay);

	
private:
	void ResetCooldownMovementGrid();
	FVector2D MapInput(FVector2D OriginalInput);

};
