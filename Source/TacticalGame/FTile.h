#pragma once

#include "CoreMinimal.h"
#include "FTile.generated.h"

USTRUCT()
struct FTile
{
	GENERATED_BODY()
		bool IsObstacle = false;
		FVector TileCenter = FVector(0, 0, 0);
		FVector SurfaceNormal = FVector(0, 0, 0);
		bool IsCover = false;
};