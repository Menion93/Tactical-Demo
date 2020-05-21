#pragma once

#include "CoreMinimal.h"
#include "SimStructs.generated.h"

USTRUCT(BlueprintType)
struct FMeleeHitSim
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool HasHit;

	UPROPERTY(BlueprintReadWrite)
	bool HasCritted;

	UPROPERTY(BlueprintReadWrite)
	float Damage;

};

USTRUCT(BlueprintType)
struct FBulletSim
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool HasHit;

	UPROPERTY(BlueprintReadWrite)
	bool HasCritted;

	UPROPERTY(BlueprintReadWrite)
	float Damage;

};

USTRUCT(BlueprintType)
struct FRoundSim
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FBulletSim> Round;
};


USTRUCT(BlueprintType)
struct FRangedWeaponSim
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FRoundSim> Rounds;
};