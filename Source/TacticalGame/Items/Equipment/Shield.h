// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Shield.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TACTICALGAME_API UShield : public UItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UShield();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldStat")
	int ShieldHealth;

	UPROPERTY(BlueprintReadWrite, Category = "ShieldStat")
	int ShieldCurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldStat")
	uint8 ShieldType;

public:

	UFUNCTION(BlueprintCallable)
	void InitShield();

};
