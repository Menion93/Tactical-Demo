#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"

class UCharacterState;

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
	TArray<TSubclassOf<class AControllableCharacter>> Array;
};