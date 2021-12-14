// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingComponent.h"
#include "Characters/GCharacter.h"
#include "Grid/Grid.h"
#include "Grid/FTile.h"

// Sets default values for this component's properties
UPathfindingComponent::UPathfindingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPathfindingComponent::Init(AGCharacter* MyCharacter)
{
	Character = MyCharacter;
}


void UPathfindingComponent::ShowShortestPath(bool Show)
{
	if (PathActor)
	{
		PathActor->SetActorHiddenInGame(!Show);
	}
}



void UPathfindingComponent::DrawShortestPath(FTileIndex TileIndex)
{
	TArray<FVector> Points;

	if (!ShortestPaths.Contains(TileIndex)) return;

	UGridUtils::UnravelPath(Character->Grid, ShortestPaths, TileIndex, Points);

	if (!PathActor)
	{
		PathActor = GetWorld()->SpawnActor<APath>(
			PathClass,
			GetOwner()->GetActorLocation(),
			FRotator::ZeroRotator);
	}

	PathActor->DrawPath(Points);
	PathActor->SetActorHiddenInGame(true);
}

void UPathfindingComponent::ComputeShortestPaths(FTileIndex TileIndex, int DistanceInTilesUnit)
{
	ShortestPaths = TMap<FTileIndex, FDijkstraNode>();
	UGridUtils::GetShortestPaths(Character->Grid, ShortestPaths, TileIndex, DistanceInTilesUnit, false);
}

bool UPathfindingComponent::TileInRange(FTile Tile, int DistanceInTilesUnit)
{
	return int(ShortestPaths[Tile.Index].Distance) <= DistanceInTilesUnit;
}

bool UPathfindingComponent::MoveTo(FTileIndex TileIndex)
{
	bool IsMoving = PathIndex != -1;

	if (!IsMoving)
	{
		MovePoints = TArray<FVector>();
		UGridUtils::UnravelPath(Character->Grid, ShortestPaths, TileIndex, MovePoints);
		PathIndex = 1;
	}

	FVector Location = Character->GetActorLocation();
	FVector FlatLocation = FVector(Location.X, Location.Y, Location.Z - Character->GetDefaultHalfHeight());
	float DistanceFromCheckpoint = FVector::Distance(FlatLocation, MovePoints[PathIndex]);
	if (DistanceFromCheckpoint < ToleranceBetweetCkpts)
	{
		if (PathIndex == MovePoints.Num() - 1)
		{
			PathIndex = -1;
			if (PathActor)
			{
				PathActor->DrawPath(TArray<FVector>());
			}
			return true;
		}

		PathIndex = (PathIndex + 1) % MovePoints.Num();
	}

	FVector Direction = MovePoints[PathIndex] - FlatLocation;
	Direction.Normalize();

	Character->AddMovementInput(Direction);
	Character->SetActorRotation(FVector(Direction.X, Direction.Y, 0).ToOrientationRotator());

	return false;
}
