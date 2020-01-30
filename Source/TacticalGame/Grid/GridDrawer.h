// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

public:
	void DrawPerimeter(TArray<FVector> Points);
	void DrawPath(TArray<FVector>);

};
