#pragma once

#include "CoreMinimal.h"
#include "Grid/Cover.h"
#include "Structs.generated.h"

class UCharacterState;
class AFireTeam;

USTRUCT(BlueprintType)
struct FCharacterStateArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCharacterState*> Array;
};

USTRUCT(BlueprintType)
struct FVectorArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Array;
};


USTRUCT(BlueprintType)
struct FCharacterClassArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AGCharacter>> Array;
};

USTRUCT(BlueprintType)
struct FFTAlliances
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AFireTeam*> Array;
};


USTRUCT(BlueprintType)
struct FLineOfSight
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	CoverTypeE CoverType;
	
	UPROPERTY(BlueprintReadWrite)
	float Distance;

	FLineOfSight() : CoverType(CoverTypeE::NONE), Distance(0.0f) {}
	FLineOfSight(CoverTypeE Cov, float Dist) : CoverType(Cov), Distance(Dist) {}

};

USTRUCT(BlueprintType)
struct FLineOfSights
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Character;

	UPROPERTY(BlueprintReadWrite)
	TMap<FTileIndex, FLineOfSight> Tiles;
};


USTRUCT(BlueprintType)
struct FSimulationOutput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Character;

	UPROPERTY(BlueprintReadWrite)
	int DamageDone;

	UPROPERTY(BlueprintReadWrite)
	float DamageDoneInPerc;

	UPROPERTY(BlueprintReadWrite)
	float RemainingHealth;

};