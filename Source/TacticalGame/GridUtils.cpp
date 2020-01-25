// Fill out your copyright notice in the Description page of Project Settings.


#include "GridUtils.h"
#include "ATileMapSet.h"
#include "Math/UnrealMath.h"


DijkstraOutput UGridUtils::GetShortestPaths(FTile* CurrentTile, int PathLenght)
{
	DijkstraOutput output;

	TArray<FDijkstraNode*> Q;

	FDijkstraNode Source;
	InitStruct(Source, CurrentTile, nullptr, 0);

	Q.Add(&Source);

	while (Q.Num() > 0)
	{
		Q.Sort();
		FDijkstraNode* node = Q[0];
		Q.RemoveAt(0);

		output.Add(node->Tile->Index, node);

		for (auto pair : node->Tile->Direction2Neighbours)
		{
			TPair<FTile*, float> tile2weight = pair.Value;

			if (node->Distance + tile2weight.Value > PathLenght) continue;

			if (!output.Contains(tile2weight.Key->Index)) 
			{
				FDijkstraNode Neighbour;
				InitStruct(Neighbour, tile2weight.Key, node, node->Distance + tile2weight.Value);

				Q.Add(&Neighbour);
				output.Add(tile2weight.Key->Index, &Neighbour);
			} 
			else if(node->Distance + tile2weight.Value < output[tile2weight.Key->Index]->Distance)
			{
				output[tile2weight.Key->Index]->Distance = node->Distance + tile2weight.Value;
				output[tile2weight.Key->Index]->Prev = node;
			}
		}
	}

	return output;
}

TArray<TPair<FVector, FVector>> UGridUtils::GetPerimeterSegments(TArray<FDijkstraNode*> Nodes, int Distance, float CellSize, float ZOffset)
{
	TArray<TPair<FVector, FVector>> Segments;

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

	return Segments;
}

void UGridUtils::InitStruct(FDijkstraNode &OutNode, FTile* tile, FDijkstraNode* prev, float distance)
{
	OutNode.Tile = tile;
	OutNode.Prev = prev;
	OutNode.Distance = distance;
}