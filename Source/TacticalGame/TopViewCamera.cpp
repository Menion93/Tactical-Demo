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

	OffsetVector = FVector::UpVector * CameraHeight - FVector::LeftVector * CameraVerticalPan;

}

void ATopViewCamera::Tick(float DeltaTime)
{
	if (FollowedActor)
	{
		SetActorLocation(FollowedActor->GetActorLocation() + OffsetVector);
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

void ATopViewCamera::MoveToTile(FTile* Tile)
{
	// Move Instantly to a Tile
	SetActorLocation(Tile->TileCenter + OffsetVector);
}

void ATopViewCamera::AttachToActor(AActor* Actor)
{
	FollowedActor = Actor;
}

void ATopViewCamera::DetachFromActor()
{
	FollowedActor = nullptr;
}
