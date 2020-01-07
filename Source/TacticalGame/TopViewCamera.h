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

	UPROPERTY(EditAnywhere)
	bool SetViewOnStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraPosition")
	float CameraHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraPosition")
	float CameraVerticalPan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraPosition")
	float CameraAngle;

private:
	bool IsLerping;
	FVector LerpDestination;
	FVector OffsetVector;

	UPROPERTY()
	AActor* FollowedActor;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void LerpToTile(FTile* Tile, float seconds);
	void MoveToTile(FTile* Tile);
	void AttachToActor(AActor* Actor);
	void DetachFromActor();
	void SetViewTarget();
};
