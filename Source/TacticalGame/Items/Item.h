// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	// Item 2D Icon (for inventory)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UseItem();
};
