#pragma once

#include "CoreMinimal.h"
#include "Items/APickable.h"
#include "FTile.generated.h"

class AGCharacter;
class AAPickable;

USTRUCT(BlueprintType)
struct FTileIndex
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool IsObstacle = false;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex Index;
		
	UPROPERTY(BlueprintReadWrite)
	FVector TileCenter = FVector(0, 0, 0);
	
	UPROPERTY(BlueprintReadWrite)
	FVector SurfaceNormal = FVector(0, 0, 0);

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Character = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AAPickable* Pickable = nullptr;
	
	TMap<FTileIndex, TPair<FTile*, float>> Direction2Neighbours;

	UPROPERTY(BlueprintReadWrite)
	bool IsCover = false;

	FString ToString()
	{
		return FString::Printf(TEXT("%s"), *TileCenter.ToString());
	}
};