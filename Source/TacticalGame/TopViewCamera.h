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

private:
	bool ControlCamera;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void LerpToActor(AActor* Actor);
	void SetLocationToActor(AActor* Actor);
	void SetCameraControl(bool Control);
};
