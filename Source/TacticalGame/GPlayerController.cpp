// Fill out your copyright notice in the Description page of Project Settings.


#include "GPlayerController.h"
#include "CombatInputController.h"
#include "WorldInputController.h"

AGPlayerController::AGPlayerController()
{
	UCombatInputController* CombatInput = NewObject<UCombatInputController>(this, TEXT("CombatInputController"));
	tag2input.Emplace(FName(TEXT("battle")), CombatInput);

	UWorldInputController* WorldInput = NewObject<UWorldInputController>(this, TEXT("WorldInputController"));
	tag2input.Emplace(FName(TEXT("world")), WorldInput);

	BindControllerInput(FName(TEXT("battle")));
}

void AGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	// keep updating the destination every tick while desired
}

void AGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATacticalGamePlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ATacticalGamePlayerController::OnSetDestinationReleased);

	//// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATacticalGamePlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATacticalGamePlayerController::MoveToTouchLocation);

	//InputComponent->BindAction("ResetVR", IE_Pressed, this, &ATacticalGamePlayerController::OnResetVR);
}

void AGPlayerController::BindControllerInput(FName MODE)
{
	UInputController* Input = tag2input[MODE];

	if (CurrentInputController)
	{
		CurrentInputController = tag2input[MODE];
	}

	CurrentInputController = tag2input[MODE];
	CurrentInputController->EnableInputController();
}

void AGPlayerController::AddInputController(FName name, UInputController* IC)
{
	if (!tag2input.Contains(name))
	{
		tag2input.Emplace(name, IC);
	}
}

