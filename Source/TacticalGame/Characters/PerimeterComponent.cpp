// Fill out your copyright notice in the Description page of Project Settings.


#include "PerimeterComponent.h"
#include "Globals/TacticalGamemode.h"
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
	TMap<FTileIndex, FDijkstraNode> PerimeterBoundariesIgnoreChar = TMap<FTileIndex, FDijkstraNode>();

	UGridUtils::GetShortestPaths(Grid, PerimeterBoundaries, TileIndex, 9999, false);
	UGridUtils::GetShortestPaths(Grid, PerimeterBoundariesIgnoreChar, TileIndex, 9999, true);

	TArray<FTileIndex> CharacterPositions;

	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	
	for (auto& FireTeam : GameMode->BattleManager->Teams)
	{
		for (auto& Char : FireTeam->Characters)
		{
			CharacterPositions.Add(Char->CurrentTileIndex);
		}
	}

	for (auto& Perimeter : Perimeters)
	{
		Perimeter->Destroy();
	}

	Perimeters = TArray<APerimeter*>();

	TArray<FVectorArray> PerimeterBlocks = UGridUtils::GetPerimeterPoints(
		Grid,
		CharacterPositions,
		PerimeterBoundariesIgnoreChar,
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