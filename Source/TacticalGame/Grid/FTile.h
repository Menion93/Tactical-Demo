#pragma once

#include "CoreMinimal.h"
#include "Items/APickable.h"
#include "FTile.generated.h"

class AGCharacter;
class AAPickable;

USTRUCT()
struct FTileIndex
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int X;

	UPROPERTY(EditAnywhere)
		int Y;

	FTileIndex() : X(0), Y(0) {}
	FTileIndex(int x, int y) : X(x), Y(y) {}
	FTileIndex(FVector2D vec) : X(vec.X), Y(vec.Y) {}

	FTileIndex operator + (FTileIndex const &obj)
	{
		FTileIndex res(X + obj.X, Y + obj.Y);
		return res;
	}

	FORCEINLINE FTileIndex operator*(int obj)
	{
		FTileIndex res(X * obj, Y * obj);
		return res;
	}

	FORCEINLINE bool operator==(const FTileIndex &Other) const
	{
		return X == Other.X && Y == Other.Y;
	}

	friend uint32 GetTypeHash(const FTileIndex& Other)
	{
		return GetTypeHash(10 * Other.X + Other.Y);
	}

	FString ToString()
	{
		return FString::Printf(TEXT("(%d, %d)"), X, Y);
	}

	FVector ToVector()
	{
		return FVector(X, Y, 0);
	}
};

USTRUCT()
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		bool IsObstacle = false;

	UPROPERTY(EditAnywhere)
		FTileIndex Index;
		
	UPROPERTY(EditAnywhere)
		FVector TileCenter = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere)
		FVector SurfaceNormal = FVector(0, 0, 0);

	AGCharacter* Character = nullptr;
	AAPickable* Pickable = nullptr;
	
	TMap<FTileIndex, TPair<FTile*, float>> Direction2Neighbours;

	UPROPERTY(EditAnywhere)
		bool IsCover = false;

	FString ToString()
	{
		return FString::Printf(TEXT("%s"), *TileCenter.ToString());
	}
};