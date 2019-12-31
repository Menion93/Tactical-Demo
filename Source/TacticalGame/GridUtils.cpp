// Fill out your copyright notice in the Description page of Project Settings.


#include "GridUtils.h"
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

TArray<FVector> UGridUtils::GetPerimeterAtDistance(TArray<FDijkstraNode*> Nodes, int Distance)
{
	TArray<FVector> result;

	for (auto node : Nodes)
	{
		if (FMath::FloorToInt(node->Distance) == Distance)
		{
			result.Emplace(node->Tile->TileCenter);
		}
	}
	return result;
}

void UGridUtils::InitStruct(FDijkstraNode &OutNode, FTile* tile, FDijkstraNode* prev, float distance)
{
	OutNode.Tile = tile;
	OutNode.Prev = prev;
	OutNode.Distance = distance;
}