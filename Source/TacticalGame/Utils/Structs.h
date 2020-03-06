#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"

USTRUCT()
struct FArrayOfArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray <FVector> Array;
};