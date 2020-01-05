// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API AGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGPlayerController();

	FVector2D HardAxis;
	FVector2D Axis;

	bool PAD_UP;
	bool PAD_RIGHT;
	bool PAD_LEFT;
	bool PAD_BOTTOM;

	bool X;
	bool Y;
	bool A;
	bool B;
	
	bool Start;
	bool Pause;

private:
	float StickUp;
	float StickRight;

public:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	bool AxisIsNotZero();
	bool HardAxisIsNotZero();

private:
	void AxisX(float Value);
	void AxisY(float Value);

	void PadX(float Value);
	void PadY(float Value);

	void InputXPressed();
	void InputYPressed();
	void InputAPressed();
	void InputBPressed();

	void InputXReleased();
	void InputYReleased();
	void InputAReleased();
	void InputBReleased();

	void StartPressed();
	void PausePressed();

	void StartReleased();
	void PauseReleased();

};
