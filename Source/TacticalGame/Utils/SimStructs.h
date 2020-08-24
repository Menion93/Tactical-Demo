#pragma once

#include "CoreMinimal.h"
#include "SimStructs.generated.h"


USTRUCT(BlueprintType)
struct FRoundSim
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		bool HasHit;

	UPROPERTY(BlueprintReadWrite)
		bool HasCritted;

	UPROPERTY(BlueprintReadWrite)
		float Damage;

	UPROPERTY(BlueprintReadWrite)
		int BulletsFired;

};

