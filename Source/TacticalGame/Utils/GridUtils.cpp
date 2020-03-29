// Fill out your copyright notice in the Description page of Project Settings.


#include "GridUtils.h"
#include "Grid/Grid.h"
#include "Math/UnrealMath.h"
#include "Kismet/GameplayStatics.h"


void UGridUtils::GetShortestPaths(AGrid* Grid, DijkstraOutput &output, FTileIndex CurrentTile, int PathLenght)
{
	TArray<FDijkstraNode> Q;

	FDijkstraNode Source(CurrentTile, FTileIndex(-1, -1), 0);

	Q.Add(Source);
	output.Add(Source.TileIndex, Source);

	while (Q.Num() > 0)
	{
		Q.Sort();
		FDijkstraNode node(Q[0].TileIndex, Q[0].Prev, Q[0].Distance);
		Q.RemoveAt(0);

		FTile Tile = Grid->GetTile(node.TileIndex);
		for (auto& pair : Tile.Direction2Neighbours)
		{
			TPair<FTile*, float> tile2weight = pair.Value;

			if (node.Distance + tile2weight.Value > PathLenght) continue;

			if (!output.Contains(tile2weight.Key->Index))
			{

				FDijkstraNode Neighbour(tile2weight.Key->Index, node.TileIndex, node.Distance + tile2weight.Value);

				Q.Add(Neighbour);
				output.Add(tile2weight.Key->Index, Neighbour);
			}
			else if (node.Distance + tile2weight.Value < output[tile2weight.Key->Index].Distance)
			{
				output[tile2weight.Key->Index].Distance = node.Distance + tile2weight.Value;
				output[tile2weight.Key->Index].Prev = node.TileIndex;
			}
		}
	}
}


TArray<FVectorArray> UGridUtils::GetPerimeterPoints(
	AGrid* Grid,
	DijkstraOutput &output,
	int Distance,
	float CellSize,
	float ZOffset)
{
	TArray<FDijkstraNode*> Nodes;

	for (auto& pair : output)
	{
		Nodes.Add(&pair.Value);
	}

	// Points of the perimeter 2 adjacent points. FVector2D instead of FVector are used becuse
	// we need the vector to be integer and thus indexable
	TMap<FTileIndex, TArray<FTileIndex>> Segments;

	// Used to retrieve floating precision vectors from the integer representation, along with the Z axis
	TMap<FTileIndex, FVector> Index2Vec;
	TArray<FVectorArray> Result;

	FTileIndex OffSetU(1, 0);
	FTileIndex OffSetR(0, 1);
	FTileIndex OffSetD(-1, 0);
	FTileIndex OffSetL(0, -1);

	TArray<FTileIndex> Directions;
	Directions.Add(OffSetU);
	Directions.Add(OffSetD);
	Directions.Add(OffSetR);
	Directions.Add(OffSetL);

	float HalfCellSize = CellSize * 0.5;
	FVector ZVector = FVector::UpVector * ZOffset;

	// Trace a line if a disconnection is found in tiles < than a certain distance --> perimeter
	for (auto Node : Nodes)
	{
		if (FMath::FloorToInt(Node->Distance) <= Distance)
		{

			for (auto Direction : Directions)
			{
				// if we find a wall, save the perimeter segment (2 points)
				FTile Tile = Grid->GetTile(Node->TileIndex);
				if (!Tile.Direction2Neighbours.Contains(Direction) ||
					FMath::FloorToInt(output[Node->TileIndex + Direction].Distance) > Distance)
				{
					FVector WallMidPoint = Tile.TileCenter + Direction.ToVector() * HalfCellSize;

					FVector A;
					FVector B;
					FTileIndex CycleMarker(1, 1);

					if (FMath::Abs(Direction.X) > 0)
					{
						A = WallMidPoint + FVector::RightVector * HalfCellSize + ZVector;
						B = WallMidPoint - FVector::RightVector * HalfCellSize + ZVector;
					}
					else
					{
						A = WallMidPoint + FVector::ForwardVector * HalfCellSize + ZVector;
						B = WallMidPoint - FVector::ForwardVector * HalfCellSize + ZVector;
					}

					FTileIndex AIndex(FMath::RoundToInt(A.X) * 10, FMath::RoundToInt(A.Y) * 10);
					FTileIndex BIndex(FMath::RoundToInt(B.X) * 10, FMath::RoundToInt(B.Y) * 10);

					if (!Segments.Contains(AIndex))
					{
						Segments.Emplace(AIndex, TArray<FTileIndex>());
					}
					else if(Segments[AIndex].Num() == 2)
					{
						AIndex = AIndex + CycleMarker;
						Segments.Emplace(AIndex, TArray<FTileIndex>());
					}

					if (!Segments.Contains(BIndex))
					{
						Segments.Emplace(BIndex, TArray<FTileIndex>());
					}
					else if (Segments[BIndex].Num() == 2)
					{
						BIndex = BIndex + CycleMarker;
						Segments.Emplace(BIndex, TArray<FTileIndex>());
					}

					Segments[AIndex].Emplace(BIndex);
					Segments[BIndex].Emplace(AIndex);
					Index2Vec.Emplace(AIndex, A);
					Index2Vec.Emplace(BIndex, B);
				}
			}
		}
	}

	TArray<FTileIndex> Visited;
	bool AreMoreBlocks = true;

	while (AreMoreBlocks)
	{
		AreMoreBlocks = AddPerimeterBlock(Result, Segments, Index2Vec, Visited);
	}

	return Result;
}

bool UGridUtils::AddPerimeterBlock(
	TArray<FVectorArray>& Result,
	TMap<FTileIndex, TArray<FTileIndex>> &Segments,
	TMap<FTileIndex, FVector>& Index2Vec,
	TArray<FTileIndex>& Visited
)
{
	bool NewBlockFound = false;
	FTileIndex PerimeterPointIndex;

	// Get first Point
	for (auto& pair : Segments)
	{
		if (!Visited.Contains(pair.Key))
		{
			PerimeterPointIndex = pair.Key;
			Visited.Emplace(pair.Key);
			NewBlockFound = true;
			break;
		}
	}

	if (!NewBlockFound)
	{
		return false;
	}

	TArray<FTileIndex> PerimeterIndexes;
	bool NewPointFound = true;

	while (NewPointFound)
	{
		NewPointFound = false;

		PerimeterIndexes.Emplace(PerimeterPointIndex);
		Visited.Emplace(PerimeterPointIndex);
		TArray<FTileIndex> Neighbours = Segments[PerimeterPointIndex];

		for (auto& Neighbour : Neighbours)
		{
			if (!PerimeterIndexes.Contains(Neighbour))
			{
				PerimeterPointIndex = Neighbour;
				NewPointFound = true;
				break;
			}
		}
	}

	FVectorArray ArrayContainer;

	for (auto& Index : PerimeterIndexes)
	{
		ArrayContainer.Array.Emplace(Index2Vec[Index]);
	}

	Result.Emplace(ArrayContainer);

	return true;
}

void UGridUtils::UnravelPath(AGrid* Grid, DijkstraOutput& ShortestPaths, FTileIndex Destination, TArray<FVector>& Out)
{
	FDijkstraNode* node = &ShortestPaths[Destination];

	// If tile is the actor's tile, dont do anything
	if (!ShortestPaths.Contains(node->Prev))
	{
		return;
	}

	TArray<FVector> Points;
	FTile Tile = Grid->GetTile(node->TileIndex);
	
	while (ShortestPaths.Contains(node->Prev))
	{
		Points.Add(Tile.TileCenter);
		node = &ShortestPaths[node->Prev];
		Tile = Grid->GetTile(node->TileIndex);
	}

	Points.Add(Tile.TileCenter);

	for (int i = Points.Num() - 1; i >= 0; i--)
	{
		Out.Add(Points[i]);
	}
}

// Build the WorldGrid in 3D dimension
void UGridUtils::BuildGrid(AActor* Map, 
							TMap<FTileIndex, FTile> &TilesMap,
							TArray<UDecalComponent*> &DebugDecals,
							UMaterialInterface* DecalMaterial,
							int Rows, 
							int Columns, 
							int CellSize, 
							bool DrawLinesInEditor) {

	int Height = Rows * CellSize;
	int Width = Columns * CellSize;


	FVector ActorLocation = Map->GetActorLocation();

	FVector OffsetVector = FVector(
		-(Height * 0.5) * (1 - 1.0 / Rows),
		-(Width * 0.5) * (1 - 1.0 / Columns),
		0);

	for (int CurrRow = 0; CurrRow < Rows; CurrRow++)
	{
		for (int CurrCol = 0; CurrCol < Columns; CurrCol++)
		{
			FVector LocalTileCenter = FVector(CurrRow * CellSize, CurrCol * CellSize, 0) + OffsetVector;
			FVector WTileCenter = Map->GetActorRotation().RotateVector(LocalTileCenter) + ActorLocation;

			FTile MyTile;
			MyTile.TileCenter = WTileCenter;

			FHitResult OutHit;
			FCollisionQueryParams CollisionParams;

			TArray<FHitResult> OutHits;


			bool hit = Map->GetWorld()->LineTraceMultiByChannel(
				OutHits,
				WTileCenter,
				WTileCenter - Map->GetActorUpVector() * 1000,
				ECollisionChannel::ECC_GameTraceChannel1,
				CollisionParams);

			if (hit)
			{
				for (auto OutHit : OutHits)
				{
					if (OutHit.bBlockingHit)
					{
						FTileIndex Index(CurrRow, CurrCol);

						MyTile.Index = Index;
						MyTile.TileCenter = OutHit.ImpactPoint;
						MyTile.SurfaceNormal = OutHit.ImpactNormal;

						TilesMap.Add(Index, MyTile);

						#if WITH_EDITOR
						if (DrawLinesInEditor)
						{
							UDecalComponent* Decal = UGameplayStatics::SpawnDecalAttached(
								DecalMaterial,
								FVector(16.0f, 32.0f, 32.0f),
								OutHit.GetComponent(),
								OutHit.BoneName,
								OutHit.ImpactPoint,
								OutHit.ImpactNormal.Rotation(),
								EAttachLocation::KeepWorldPosition,
								999);

							DebugDecals.Add(Decal);
						}
						#endif
					}
					else
					{
						break;
					}
				}
			}

		}
	}

	// Now link cells
	FTileIndex OffSetU(1, 0);
	FTileIndex OffSetR(0, 1);
	FTileIndex OffSetIQuad(1, 1);
	FTileIndex OffSet4Quad(-1, 1);

	TArray<FTileIndex> Neighbour;
	Neighbour.Add(OffSetU);
	Neighbour.Add(OffSetR);
	Neighbour.Add(OffSetIQuad);
	Neighbour.Add(OffSet4Quad);

	for (auto& tile : TilesMap)
	{
		for (int j = 0; j < 2; j++)
		{
			for (auto OffSetVec : Neighbour)
			{
				FTileIndex Direction = (OffSetVec * (-j)) + (OffSetVec * (1 - j));
				FTileIndex NeighbourKey = tile.Key + Direction;

				if (TilesMap.Contains(NeighbourKey))
				{
					float Weight = FMath::Abs(Direction.X) == FMath::Abs(Direction.Y) ? 1.05 : 1.0;

					TPair<FTile*, float> Pair(&TilesMap[NeighbourKey], Weight);
					tile.Value.Direction2Neighbours.Add(Direction, Pair);
				}
			}
		}
	}

}