// Fill out your copyright notice in the Description page of Project Settings.


#include "TopViewCamera.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathVectorCommon.h"



ATopViewCamera::ATopViewCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATopViewCamera::BeginPlay()
{
	if (SetViewOnStart)
	{
		SetViewTarget();
	}

	//SetActorRelativeRotation(FRotator(CameraAngle, 0, 0));

	OffsetVector = - FVector::ForwardVector * CameraVerticalPan;
}

void ATopViewCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowedActor)
	{ 
		const FRotator PitchRotation(CameraAngle, 0, 0);

		FVector ActorUpVector = PitchRotation.RotateVector(FVector::UpVector * CameraDistanceFromActor) + FollowedActor->GetActorLocation();
		SetActorLocation(ActorUpVector);

		SetActorRotation((FollowedActor->GetActorLocation() - GetActorLocation()).ToOrientationRotator());
	}
	else if (IsLerping)
	{
		if (GetActorLocation() == LerpDestination)
		{
			IsLerping = false;
		}
		SetActorLocation(FMath::Lerp(GetActorLocation(), LerpDestination, DeltaTime));
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

void ATopViewCamera::LerpToTile(FTile* Tile, float seconds)
{
	// Lerp to Actor, then update grid position
	LerpDestination = Tile->TileCenter + OffsetVector;
	IsLerping = true;
}

void ATopViewCamera::LookAtPosition(FVector Position)
{
	const FRotator PitchRotation(CameraAngle, 0, 0);
	FVector ActorUpVector = PitchRotation.RotateVector(FVector::UpVector * CameraDistanceFromActor) + Position;
	
	SetActorLocation(ActorUpVector);
	SetActorRotation((Position - GetActorLocation()).ToOrientationRotator());
}

void ATopViewCamera::AttachToActor(AActor* Actor)
{
	FollowedActor = Actor;
}

void ATopViewCamera::DetachFromActor()
{
	FollowedActor = nullptr;
}
