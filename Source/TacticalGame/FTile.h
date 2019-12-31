#pragma once

#include "CoreMinimal.h"
#include "FTile.generated.h"


USTRUCT()
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		bool IsObstacle = false;

	UPROPERTY(EditAnywhere)
		FVector2D Index;
		
	UPROPERTY(EditAnywhere)
		FVector TileCenter = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere)
		FVector SurfaceNormal = FVector(0, 0, 0);
	
	TMap<FVector2D, TPair<FTile*, float>> Direction2Neighbours;

	UPROPERTY(EditAnywhere)
		bool IsCover = false;
};

