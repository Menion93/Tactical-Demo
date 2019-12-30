// Fill out your copyright notice in the Description page of Project Settings.


#include "TopViewCamera.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathVectorCommon.h"



ATopViewCamera::ATopViewCamera()
{

}

void ATopViewCamera::BeginPlay()
{
	if (SetViewOnStart)
	{
		SetViewTarget();
	}

	SetActorRelativeRotation(FRotator(CameraAngle, 0, 0));
}

void ATopViewCamera::Tick(float DeltaTime)
{
	if (ControlCamera)
	{

	}
	else if(FollowedActor)
	{
		FVector Destination = FollowedActor->GetActorLocation() + FVector::UpVector * CameraHeight - FVector::LeftVector * CameraVerticalPan;
		SetActorLocation(FMath::Lerp(GetActorLocation(), Destination, DeltaTime));
	}

}

void ATopViewCamera::SetViewTarget()
{
	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* Pc = World->GetFirstPlayerController();
		if (Pc)
		{
			Pc->SetViewTarget(this);
		}
	}
}

void ATopViewCamera::LerpToActor(AActor* Actor, float seconds)
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

void ATopViewCamera::AttachToActor(AActor* Actor)
{
	FollowedActor = Actor;
}

void ATopViewCamera::DeattachFromActor()
{
	FollowedActor = nullptr;
}
