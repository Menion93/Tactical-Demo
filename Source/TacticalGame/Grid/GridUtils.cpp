// Fill out your copyright notice in the Description page of Project Settings.


#include "GridUtils.h"
#include "ATileMapSet.h"
#include "Math/UnrealMath.h"
#include "Kismet/GameplayStatics.h"


void UGridUtils::GetShortestPaths(DijkstraOutput &output, FTile* CurrentTile, int PathLenght)
{
	TArray<FDijkstraNode> Q;

	FDijkstraNode Source;
	InitStruct(Source, CurrentTile, nullptr, 0);

	Q.Add(Source);

	while (Q.Num() > 0)
	{
		Q.Sort();
		FDijkstraNode node = Q[0];
		Q.RemoveAt(0);

		output.Add(node.Tile->Index, node);


		for (auto& pair : node.Tile->Direction2Neighbours)
		{
			TPair<FTile*, float> tile2weight = pair.Value;

			if (node.Distance + tile2weight.Value > PathLenght) continue;

			if (!output.Contains(tile2weight.Key->Index)) 
			{
				FDijkstraNode Neighbour;
				InitStruct(Neighbour, tile2weight.Key, &node, node.Distance + tile2weight.Value);

				Q.Add(Neighbour);
				output.Add(tile2weight.Key->Index, Neighbour);
			} 
			else if(node.Distance + tile2weight.Value < output[tile2weight.Key->Index].Distance)
			{
				output[tile2weight.Key->Index].Distance = node.Distance + tile2weight.Value;
				output[tile2weight.Key->Index].Prev = &node;
			}
		}
	}
}

void UGridUtils::InitStruct(FDijkstraNode &OutNode, FTile* tile, FDijkstraNode* prev, float distance)
{
	OutNode.Tile = tile;
	OutNode.Prev = prev;
	OutNode.Distance = distance;
}

TArray<FVector> UGridUtils::GetPerimeterPoints(TArray<FDijkstraNode*> Nodes, int Distance, float CellSize, float ZOffset)
{
	TArray<TPair<FVector, FVector>> Segments;
	TArray<FVector> Result;

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
		UE_LOG(LogTemp, Warning, TEXT("yolo2d"));
		UE_LOG(LogTemp, Warning, TEXT("%d"), Node->Distance);
		UE_LOG(LogTemp, Warning, TEXT("X is %d"), Node->Tile->Index.X);
		UE_LOG(LogTemp, Warning, TEXT("Y is %d"), Node->Tile->Index.Y);


		if (FMath::FloorToInt(Node->Distance) <= Distance)
		{
			for (auto Direction : Directions)
			{
				// if we find a wall, save the perimeter segment (2 points)
				if (!Node->Tile->Direction2Neighbours.Contains(Direction))
				{
					FVector WallMidPoint = Node->Tile->TileCenter + Direction.ToVector() * HalfCellSize;

					FVector A;
					FVector B;

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
					Segments.Emplace(TPair<FVector, FVector>(A, B));
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("yolo3"));

	// Simplify Segments
	Result.Add(Segments[0].Key);
	Result.Add(Segments[0].Value);

	for (int i=1; i<Segments.Num(); i++)
	{
		for (int j = 1; j < Segments.Num(); j++)
		{
			if (Result[Result.Num()-1] == Segments[j].Key)
			{
				Result.Add(Segments[j].Key);
				Result.Add(Segments[j].Value);
			}
			else if (Result[Result.Num() - 1] == Segments[j].Value)
			{
				Result.Add(Segments[j].Value);
				Result.Add(Segments[j].Key);
			}
		}
	}
	return Result;
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
	FTileIndex OffSetL(0, 1);
	FTileIndex OffSetIQuad(1, 1);
	FTileIndex OffSet2Quad(-1, 1);

	TArray<FTileIndex> Neighbour;
	Neighbour.Add(OffSetU);
	Neighbour.Add(OffSetL);
	Neighbour.Add(OffSetIQuad);
	Neighbour.Add(OffSet2Quad);

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
					float Weight = FMath::Abs(Direction.X) == FMath::Abs(Direction.Y) ? 1.05 : 1;

					TPair<FTile*, float> Pair(&TilesMap[NeighbourKey], Weight);
					tile.Value.Direction2Neighbours.Add(Direction, Pair);
				}
			}
		}
	}

}