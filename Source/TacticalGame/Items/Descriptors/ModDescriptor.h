// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ModDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UModDescriptor : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModStat")
		char TypeMod;   //Barrel, FireRate, Damage etc.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModStat")
		int BonusMod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModStat")
		int SlotMod;   //che livello di slot è necessario, oppure quanti slot occupa una mod

};
