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
		FVector TileCenter = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere)
		FVector SurfaceNormal = FVector(0, 0, 0);
	
		TArray<FTile*> Neighbours;
	
	UPROPERTY(EditAnywhere)
		bool IsCover = false;
};