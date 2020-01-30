// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PerkDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UPerkDescriptor : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerkStat")
		char PerkName;   //si verifica da codice quale sia il nome del perk e in base alla corrispondenza all'interno di un eventuale array, si va all'abilità corrispondente.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerkStat")
		int PerkCooldown;   //da qui si può prendere eventuale cooldown per riutilizzare l'abilità derivante dal perk

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerkStat")
		int BonusPerk;   //qualora il perk si limiti a dare un bonus ad una statistica

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerkStat")
		int PerkDuration;  //regola la durata del perk e/o dell'abilità corrispondente che verrebbe attivata
};
