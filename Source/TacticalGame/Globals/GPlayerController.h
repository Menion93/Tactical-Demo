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

	bool Axis_DOWN;

	bool PAD_UP;
	bool PAD_UP_DOWN;

	bool PAD_RIGHT;
	bool PAD_RIGHT_DOWN;

	bool PAD_LEFT;
	bool PAD_LEFT_DOWN;

	bool PAD_BOTTOM;
	bool PAD_BOTTOM_DOWN;

	bool X;
	bool X_DOWN;

	bool Y;
	bool Y_DOWN;

	bool A;
	bool A_DOWN;

	bool B;
	bool B_DOWN;

	bool Start;
	bool Start_DOWN;

	bool Pause;
	bool Pause_DOWN;

private:
	float StickUp;
	float StickRight;

	float second;

public:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

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

	void HandleActionInputPressed(bool& down, bool& button);
	void HandleActionInputReleased(bool& down, bool& button);

};