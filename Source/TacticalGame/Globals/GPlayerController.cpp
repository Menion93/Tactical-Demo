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

}

void AGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("StickAxisX", this, &AGPlayerController::AxisX);
	InputComponent->BindAxis("StickAxisY", this, &AGPlayerController::AxisY);

	InputComponent->BindAction("A", EInputEvent::IE_Pressed, this, &AGPlayerController::InputAPressed);
	InputComponent->BindAction("A", EInputEvent::IE_Released, this, &AGPlayerController::InputAReleased);

	InputComponent->BindAction("B", EInputEvent::IE_Pressed, this, &AGPlayerController::InputBPressed);
	InputComponent->BindAction("B", EInputEvent::IE_Released, this, &AGPlayerController::InputBReleased);

	InputComponent->BindAction("X", EInputEvent::IE_Pressed, this, &AGPlayerController::InputXPressed);
	InputComponent->BindAction("X", EInputEvent::IE_Released, this, &AGPlayerController::InputXReleased);

	InputComponent->BindAction("Y", EInputEvent::IE_Pressed, this, &AGPlayerController::InputYPressed);
	InputComponent->BindAction("Y", EInputEvent::IE_Released, this, &AGPlayerController::InputYReleased);

	InputComponent->BindAction("Start", EInputEvent::IE_Pressed, this, &AGPlayerController::StartPressed);
	InputComponent->BindAction("Start", EInputEvent::IE_Released, this, &AGPlayerController::StartReleased);

	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &AGPlayerController::PausePressed);
	InputComponent->BindAction("Pause", EInputEvent::IE_Released, this, &AGPlayerController::PauseReleased);

	InputComponent->BindAction("R1", EInputEvent::IE_Pressed, this, &AGPlayerController::R1Pressed);
	InputComponent->BindAction("R1", EInputEvent::IE_Released, this, &AGPlayerController::R1Released);

}

void AGPlayerController::HandleActionInputPressed(bool& down, bool& button)
{
	button = true;
	down = true;
}

void AGPlayerController::HandleActionInputReleased(bool& down, bool& button)
{
	button = false;
	down = false;
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

void AGPlayerController::InputXPressed()
{
	HandleActionInputPressed(X, X_DOWN);
}

void AGPlayerController::InputYPressed()
{
	HandleActionInputPressed(Y, Y_DOWN);
}

void AGPlayerController::InputAPressed()
{
	HandleActionInputPressed(A, A_DOWN);
}

void AGPlayerController::InputBPressed()
{
	HandleActionInputPressed(B, B_DOWN);
}

void AGPlayerController::InputXReleased()
{
	HandleActionInputReleased(X_DOWN, X);
}

void AGPlayerController::InputYReleased()
{

	HandleActionInputReleased(Y_DOWN, Y);
}

void AGPlayerController::InputAReleased()
{
	HandleActionInputReleased(A_DOWN, A);
}

void AGPlayerController::InputBReleased()
{
	HandleActionInputReleased(B_DOWN, B);
}

void AGPlayerController::StartPressed()
{
	HandleActionInputPressed(Start_DOWN, Start);
}

void AGPlayerController::PausePressed()
{
	HandleActionInputPressed(Pause_DOWN, Pause);
}

void AGPlayerController::StartReleased()
{
	HandleActionInputReleased(Start_DOWN, Start);
}

void AGPlayerController::PauseReleased()
{
	HandleActionInputReleased(Pause_DOWN, Pause);
}

void AGPlayerController::R1Pressed()
{
	HandleActionInputPressed(R1_DOWN, R1);
}

void AGPlayerController::R1Released()
{
	HandleActionInputReleased(R1_DOWN, R1);
}