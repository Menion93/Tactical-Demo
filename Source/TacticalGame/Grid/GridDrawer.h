// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/SplineComponent.h"
#include "GridDrawer.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UGridDrawer : public UObject
{
	GENERATED_BODY()
	
public:
	UGridDrawer();

	FPrimitiveDrawInterface* PDI;

	UPROPERTY()
	USplineComponent* Perimeter;

	UPROPERTY()
	USplineComponent* Path;

public:
	void DrawPerimeter(TArray<TPair<FVector, FVector>> segments, FLinearColor Color, float Tickness);
	void DrawPath(TArray<FVector>);

};
