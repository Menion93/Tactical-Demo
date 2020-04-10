// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GPlayerController.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class TACTICALGAME_API AGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGPlayerController();

	UPROPERTY(BlueprintReadWrite)
	FVector2D LHardAxis;

	UPROPERTY(BlueprintReadWrite)
	FVector2D LAxis;

	UPROPERTY(BlueprintReadWrite)
	FVector2D RHardAxis;

	UPROPERTY(BlueprintReadWrite)
	FVector2D RAxis;

	UPROPERTY(BlueprintReadWrite)
	bool LAxis_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool RAxis_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool PAD_UP;
	UPROPERTY(BlueprintReadWrite)
	bool PAD_UP_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool PAD_RIGHT;

	UPROPERTY(BlueprintReadWrite)
	bool PAD_RIGHT_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool PAD_LEFT;
	UPROPERTY(BlueprintReadWrite)
	bool PAD_LEFT_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool PAD_BOTTOM;
	UPROPERTY(BlueprintReadWrite)
	bool PAD_BOTTOM_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool X;
	UPROPERTY(BlueprintReadWrite)
	bool X_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool Y;
	UPROPERTY(BlueprintReadWrite)
	bool Y_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool A;
	UPROPERTY(BlueprintReadWrite)
	bool A_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool B;
	UPROPERTY(BlueprintReadWrite)
	bool B_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool R1;
	UPROPERTY(BlueprintReadWrite)
	bool R1_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool R2;
	UPROPERTY(BlueprintReadWrite)
	bool R2_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool L1;
	UPROPERTY(BlueprintReadWrite)
	bool L1_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool L2;
	UPROPERTY(BlueprintReadWrite)
	bool L2_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool Start;
	UPROPERTY(BlueprintReadWrite)
	bool Start_DOWN;

	UPROPERTY(BlueprintReadWrite)
	bool MyPause;
	UPROPERTY(BlueprintReadWrite)
	bool Pause_DOWN;

private:
	float LStickUp;
	float LStickRight;
	float LSecond;

	float RStickUp;
	float RStickRight;
	float RSecond;

public:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:
	void LAxisX(float Value);
	void LAxisY(float Value);

	void RAxisX(float Value);
	void RAxisY(float Value);

	void PadX(float Value);
	void PadY(float Value);
	void InputX(float Value);
	void InputY(float Value);
	void InputA(float Value);
	void InputB(float Value);
	void InputStart(float Value);
	void InputPause(float Value);
	void InputR1(float Value);
	void InputR2(float Value);
	void InputL1(float Value);
	void InputL2(float Value);

	void HandleActionInput(bool& down, bool& button, float value);

};