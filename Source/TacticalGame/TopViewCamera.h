// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "FTile.h"
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
	FTile CurrentTile;

	UPROPERTY(EditAnywhere)
	bool SetViewOnStart;

	float CameraHeight;
	float CameraVerticalPan;
	float CameraAngle;

private:
	bool ControlCamera;
	AActor* FollowedActor;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void LerpToActor(AActor* Actor, float seconds);
	void SetLocationToActor(AActor* Actor);
	void SetCameraControl(bool Control);
	void AttachToActor(AActor* Actor);
	void DeattachFromActor();
	void SetViewTarget();
};
