// Fill out your copyright notice in the Description page of Project Settings.


#include "TopViewCamera.h"


ATopViewCamera::ATopViewCamera()
{

}

void ATopViewCamera::BeginPlay()
{

}

void ATopViewCamera::Tick(float DeltaTime)
{
	if (ControlCamera)
	{

	}

}

void ATopViewCamera::LerpToActor(AActor* Actor) 
{
	// Lerp to Actor, then update grid position

}

void ATopViewCamera::SetLocationToActor(AActor* Actor)
{
	// Move Instantly to Actor, then update grid position

}

void ATopViewCamera::SetCameraControl(bool Control)
{
	ControlCamera = Control;
}
