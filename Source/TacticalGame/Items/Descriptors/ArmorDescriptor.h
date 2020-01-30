// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArmorDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UArmorDescriptor : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int CharacterSpeed;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int CharacterDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int BonusHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		char ArmorType;   //di pelle, di ferro, di acciaio, di lega futuristica o altro. In base al tipo, cambiano i tre bonus soprastanti forniti al pg

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int SlotMod;   //quanti slot per mod ha

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int SlotLevel;  //eventuale livello degli slot
	
};
