// Fill out your copyright notice in the Description page of Project Settings.


#include "GPlayerController.h"

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

	InputComponent->BindAxis("MoveForward", this, &AGPlayerController::AxisY);
	InputComponent->BindAxis("MoveRight", this, &AGPlayerController::AxisX);

	InputComponent->BindAxis("StickAxisX", this, &AGPlayerController::AxisX);
	InputComponent->BindAxis("StickAxisY", this, &AGPlayerController::AxisY);

}

void AGPlayerController::AxisX(float Value)
{
	StickRight = Value;
	HardAxis = FVector2D(FMath::RoundToInt(StickUp), FMath::RoundToInt(StickRight));
	Axis = FVector2D(StickUp, StickRight);
}

void AGPlayerController::AxisY(float Value)
{
	StickUp = Value;
	HardAxis = FVector2D(FMath::RoundToInt(StickUp), FMath::RoundToInt(StickRight));
	Axis = FVector2D(StickUp, StickRight);
}

void AGPlayerController::PadX(float Value)
{
	int Direction = FMath::RoundToInt(Value);

	PAD_RIGHT = Direction > 0;
	PAD_LEFT = Direction < 0;

	PAD_UP = false;
	PAD_BOTTOM = PAD_UP;

}

void AGPlayerController::PadY(float Value)
{
	int Direction = FMath::RoundToInt(Value);

	PAD_UP = Direction > 0;
	PAD_BOTTOM = Direction < 0;

	PAD_RIGHT = false;
	PAD_LEFT = PAD_RIGHT;
}

void AGPlayerController::InputXPressed()
{
	X = true;
}

void AGPlayerController::InputYPressed()
{
	Y = true;
}

void AGPlayerController::InputAPressed()
{
	A = true;
}

void AGPlayerController::InputBPressed()
{
	B = true;
}

void AGPlayerController::InputXReleased()
{
	X = false;
}

void AGPlayerController::InputYReleased()
{
	Y = false;
}

void AGPlayerController::InputAReleased()
{
	A = false;
}

void AGPlayerController::InputBReleased()
{
	B = false;
}

void AGPlayerController::StartPressed()
{
	Start = true;
}

void AGPlayerController::PausePressed()
{
	Pause = true;
}

void AGPlayerController::StartReleased()
{
	Start = false;
}

void AGPlayerController::PauseReleased()
{
	Pause = false;
}

bool AGPlayerController::HardAxisIsNotZero()
{
	return HardAxis.X + HardAxis.Y > 0;
}

bool AGPlayerController::AxisIsNotZero()
{
	return Axis.X + Axis.Y > 0;
}

