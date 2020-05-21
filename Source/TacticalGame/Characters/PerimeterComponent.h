// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grid/FTile.h"
#include "Utils/GridUtils.h"
#include "Grid/Perimeter.h"
#include "PerimeterComponent.generated.h"

class AGrid;


UCLASS( ClassGroup=(PerimeterComponent), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UPerimeterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPerimeterComponent();

public:

	UPROPERTY(BlueprintReadWrite)
	TMap<FTileIndex, FDijkstraNode> PerimeterBoundaries;

	UPROPERTY(BlueprintReadWrite)
	TArray<APerimeter*> Perimeters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APerimeter> PerimeterClass;

	UPROPERTY(BlueprintReadWrite)
	AGrid* Grid;

public:
	UFUNCTION(BlueprintCallable)
	void Init(AGrid* MyGrid);

	UFUNCTION(BlueprintCallable)
	void ShowPerimeter(bool Show);

	UFUNCTION(BlueprintCallable)
	void ComputePerimeterPoints(FTileIndex TileIndex, int DistanceInTilesUnit);

		
};
