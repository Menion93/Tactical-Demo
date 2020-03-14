// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Perk.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UPerk : public UItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPerk();

protected:
	// Called when the game starts


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerkStat")
	FString PerkName;



public:	
	//void SetupPerk();

	//void ActivatePerk();

		
};
