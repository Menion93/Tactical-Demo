// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Grid/FTile.h"
#include "GameFramework/Actor.h"
#include "Globals/GPlayerController.h"
#include "TopViewCamera.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API ATopViewCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	ATopViewCamera();

	AGPlayerController* Input;

	UPROPERTY(EditAnywhere)
	bool SetViewOnStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraPosition")
	float CameraNeutralHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement")
	float LerpPanSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement")
	float LerpPanThreshold = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Pitch Rotation")
	float PitchStartAngle = 45;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Pitch Rotation")
	float PitchMinAngle = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Pitch Rotation")
	float PitchMaxAngle = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Pitch Rotation")
	float PitchSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Yaw Rotation")
	float TimeYawRotation = 0.3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Yaw Rotation")
	float YawMaxRotationSpeed = 11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Yaw Rotation")
	float YawMinRotationSpeed = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Yaw Rotation")
	float YawRotationDecelFactor = 0.914;

	FVector LastPosition;

	float YawAngle = 45;
	int YawIndex = 0;

	bool InputActive = true;

	UPROPERTY(BlueprintReadWrite)
	bool IsPanLerping;

	UPROPERTY(BlueprintReadWrite)
	bool IsYawLerping;

private:


	FVector LerpDestination;
	float PitchInterp = 0;

	float YawStartAngle;
	float YawTargetAngle;
	float YawInterp;
	float YawRotationCurrentSpeed;

	float GetPitchAngle();
	float GetYawAngle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LerpToPosition(FVector Position);

	UFUNCTION(BlueprintCallable)
	void LookAtPosition(FVector Position);

	UFUNCTION(BlueprintCallable)
	void SetViewTarget();

	UFUNCTION(BlueprintCallable)
	void EnableCameraInput(bool Enable);

	UFUNCTION(BlueprintCallable)
	void ComputePitchRotation(float PitchDirection, float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void ComputeYawRotation(float PitchDirection);
};
