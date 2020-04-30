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

	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());

	//SetActorRelativeRotation(FRotator(CameraAngle, 0, 0));
	PitchInterp = (PitchStartAngle - PitchMaxAngle) / (PitchMinAngle - PitchMaxAngle);
}

void ATopViewCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPanLerping)
	{
		if (FVector::Distance(GetActorLocation(), LerpDestination) < LerpPanThreshold)
		{
			IsPanLerping = false;
		}

		SetActorLocation(FMath::Lerp(GetActorLocation(), LerpDestination, DeltaTime * LerpPanSpeed));
	}
	else if (IsYawLerping)
	{
		if (FMath::IsNearlyEqual(YawInterp, 1.0f))
		{
			IsYawLerping = false;
		}

		YawRotationCurrentSpeed = FMath::Clamp(YawRotationCurrentSpeed * YawRotationDecelFactor,
			YawMinRotationSpeed,
			YawMaxRotationSpeed);

		YawInterp = FMath::Clamp(YawInterp + DeltaTime * YawRotationCurrentSpeed, 0.0f, 1.0f);

		const FRotator PitchRotation(GetPitchAngle(), GetYawAngle(), 0);
		FVector ActorUpVector = PitchRotation.RotateVector(FVector::UpVector * CameraNeutralHeight) + LastPosition;

		SetActorLocation(ActorUpVector);
		SetActorRotation((LastPosition - GetActorLocation()).ToOrientationRotator());
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

void ATopViewCamera::LerpToPosition(FVector Position)
{
	LastPosition = Position;
	const FRotator PitchRotation(GetPitchAngle(), YawAngle * YawIndex, 0);
	LerpDestination = PitchRotation.RotateVector(FVector::UpVector * CameraNeutralHeight) + Position;
	IsPanLerping = true;
}

void ATopViewCamera::LookAtPosition(FVector Position)
{
	IsPanLerping = false;
	IsYawLerping = false;
	LastPosition = Position;
	const FRotator PitchRotation(GetPitchAngle(), YawAngle * YawIndex, 0);
	FVector ActorUpVector = PitchRotation.RotateVector(FVector::UpVector * CameraNeutralHeight) + Position;
	
	SetActorLocation(ActorUpVector);
	SetActorRotation((Position - GetActorLocation()).ToOrientationRotator());
}

void ATopViewCamera::ComputePitchRotation(float PitchDirection, float DeltaTime)
{
	PitchInterp = FMath::Clamp(PitchInterp + PitchDirection * PitchSpeed * DeltaTime, 0.0f, 1.0f);
	LookAtPosition(LastPosition);
}

void ATopViewCamera::ComputeYawRotation(float YawDirection)
{
	if (!IsYawLerping)
	{
		YawRotationCurrentSpeed = YawMaxRotationSpeed;
		YawStartAngle = YawIndex * YawAngle;
		YawIndex = YawDirection > 0 ? ++YawIndex : --YawIndex;
		YawTargetAngle = YawIndex * YawAngle;
		YawInterp = 0;
		IsYawLerping = true;
	}
}

float ATopViewCamera::GetYawAngle()
{
	return FMath::Lerp(YawStartAngle, YawTargetAngle, YawInterp);
}

float ATopViewCamera::GetPitchAngle()
{
	return FMath::Lerp(PitchMinAngle, PitchMaxAngle, PitchInterp);
}

void ATopViewCamera::EnableCameraInput(bool Enable)
{
	InputActive = Enable;
}
