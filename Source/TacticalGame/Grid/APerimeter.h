// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/SplineComponent.h"
#include "APerimeter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API APerimeter : public AActor
{
	GENERATED_BODY()
	
public:
	APerimeter();

	UPROPERTY(BlueprintReadWrite)
	USplineComponent* Perimeter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;

public:
	void DrawPerimeter(TArray<FVector> Points);
};
