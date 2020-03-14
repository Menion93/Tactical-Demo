// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Bag.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UBag : public UItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBag();


public:

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItems();
};
