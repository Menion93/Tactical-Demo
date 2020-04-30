// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Mod.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UMod : public UItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMod();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModStat")
	FString TypeMod;   //Barrel, FireRate, Damage etc.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModStat")
	int BonusMod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModStat")
	int SlotMod;   //che livello di slot è necessario, oppure quanti slot occupa una mod


		
};
