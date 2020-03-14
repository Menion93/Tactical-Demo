// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UAction : public UObject
{
	GENERATED_BODY()

public:
	UAction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionName;

public:

	UFUNCTION(BlueprintNativeEvent)
	void PlayAction();
	
};
