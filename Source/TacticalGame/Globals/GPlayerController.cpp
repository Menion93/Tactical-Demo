// Fill out your copyright notice in the Description page of Project Settings.


#include "GPlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"

AGPlayerController::AGPlayerController()
{

}

void AGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("CIAOOOdf"))
}


void AGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("StickAxisX", this, &AGPlayerController::AxisX);
	InputComponent->BindAxis("StickAxisY", this, &AGPlayerController::AxisY);
	InputComponent->BindAxis("A", this, &AGPlayerController::InputA);
	InputComponent->BindAxis("B", this, &AGPlayerController::InputB);
	InputComponent->BindAxis("X", this, &AGPlayerController::InputX);
	InputComponent->BindAxis("Y", this, &AGPlayerController::InputY);
	InputComponent->BindAxis("Start", this, &AGPlayerController::InputStart);
	InputComponent->BindAxis("Pause", this, &AGPlayerController::InputPause);
	InputComponent->BindAxis("R1", this, &AGPlayerController::InputR1);
	InputComponent->BindAxis("R2", this, &AGPlayerController::InputR2);
	InputComponent->BindAxis("L1", this, &AGPlayerController::InputL1);
	InputComponent->BindAxis("L2", this, &AGPlayerController::InputL2);
}

void AGPlayerController::HandleActionInput(bool& button, bool& down, float value)
{
	down = !button && int(value);
	button = int(value) > 0;
}


void AGPlayerController::AxisX(float Value)
{
	if (second)
	{
		Axis_DOWN = !FMath::RoundToInt(StickUp) && FMath::RoundToInt(Value) || Axis_DOWN;
		second = false;
	}
	else
	{
		Axis_DOWN = !FMath::RoundToInt(StickUp) && FMath::RoundToInt(Value);
		second = true;
	}

	StickUp = Value;
	HardAxis = FVector2D(FMath::RoundToInt(StickUp), FMath::RoundToInt(StickRight));
	Axis = FVector2D(StickUp, StickRight);
}

void AGPlayerController::AxisY(float Value)
{
	if (second)
	{
		Axis_DOWN = !FMath::RoundToInt(StickRight) && FMath::RoundToInt(Value) || Axis_DOWN;
		second = false;
	}
	else
	{
		Axis_DOWN = !FMath::RoundToInt(StickRight) && FMath::RoundToInt(Value);
		second = true;
	}

	StickRight = Value;
	HardAxis = FVector2D(FMath::RoundToInt(StickUp), FMath::RoundToInt(StickRight));
	Axis = FVector2D(StickUp, StickRight);
}

void AGPlayerController::PadX(float Value)
{
	int Direction = FMath::RoundToInt(Value);

	PAD_UP = Direction > 0;
	PAD_BOTTOM = Direction < 0;

	PAD_RIGHT = false;
	PAD_LEFT = PAD_RIGHT;
}

void AGPlayerController::PadY(float Value)
{
	int Direction = FMath::RoundToInt(Value);

	PAD_RIGHT = Direction > 0;
	PAD_LEFT = Direction < 0;

	PAD_UP = false;
	PAD_BOTTOM = PAD_UP;
}

void AGPlayerController::InputX(float Value)
{
	HandleActionInput(X, X_DOWN, Value);
}

void AGPlayerController::InputY(float Value)
{
	HandleActionInput(Y, Y_DOWN, Value);
}

void AGPlayerController::InputA(float Value)
{
	HandleActionInput(A, A_DOWN, Value);
}

void AGPlayerController::InputB(float Value)
{
	HandleActionInput(B, B_DOWN, Value);
}

void AGPlayerController::InputStart(float Value)
{
	HandleActionInput(Start, Start_DOWN, Value);
}

void AGPlayerController::InputPause(float Value)
{
	HandleActionInput(MyPause, Pause_DOWN, Value);
}

void AGPlayerController::InputR1(float Value)
{
	HandleActionInput(R1, R1_DOWN, Value);
}

void AGPlayerController::InputR2(float Value)
{
	HandleActionInput(R2, R2_DOWN, Value);

}

void AGPlayerController::InputL1(float Value)
{
	HandleActionInput(L1, L1_DOWN, Value);

}

void AGPlayerController::InputL2(float Value)
{
	HandleActionInput(L2, L2_DOWN, Value);
}