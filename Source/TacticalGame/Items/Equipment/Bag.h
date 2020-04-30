// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "BattleSystem/Actions/Actionable.h"
#include "Bag.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UBag : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBag();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UItem>> DefaultItemClasses;

	UPROPERTY(BlueprintReadWrite)
	TArray<UItem*> Items;

public:

	UFUNCTION(BlueprintCallable)
	void LoadDefaultItems();

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItems();

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetOffensiveItems();

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetSupportItems();
};
