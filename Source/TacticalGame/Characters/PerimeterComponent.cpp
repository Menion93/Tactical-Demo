// Fill out your copyright notice in the Description page of Project Settings.


#include "PerimeterComponent.h"
#include "Grid/Grid.h"

// Sets default values for this component's properties
UPerimeterComponent::UPerimeterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPerimeterComponent::Init(AGrid* MyGrid)
{
	Grid = MyGrid;
}


void UPerimeterComponent::ShowPerimeter(bool Show)
{
	for (auto& p : Perimeters)
	{
		p->SetActorHiddenInGame(!Show);
	}
}

void UPerimeterComponent::ComputePerimeterPoints(FTileIndex TileIndex, int DistanceInTilesUnit)
{
	PerimeterBoundaries = TMap<FTileIndex, FDijkstraNode>();
	UGridUtils::GetShortestPaths(Grid, PerimeterBoundaries, TileIndex, 9999, true);

	for (auto& Perimeter : Perimeters)
	{
		Perimeter->Destroy();
	}

	Perimeters = TArray<APerimeter*>();

	TArray<FVectorArray> PerimeterBlocks = UGridUtils::GetPerimeterPoints(
		Grid,
		PerimeterBoundaries,
		DistanceInTilesUnit,
		Grid->CellSize,
		Grid->PerimeterVOffset);

	for (auto& perimeter : PerimeterBlocks)
	{
		APerimeter* Perimeter = GetWorld()->SpawnActor<APerimeter>(
			PerimeterClass, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

		Perimeter->DrawPerimeter(perimeter.Array);
		Perimeter->SetActorHiddenInGame(true);
		Perimeters.Add(Perimeter);
	}
}