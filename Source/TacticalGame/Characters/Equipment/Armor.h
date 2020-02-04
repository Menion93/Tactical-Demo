// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Armor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UArmor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int CharacterSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int CharacterDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int BonusHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		FString ArmorType;   //di pelle, di ferro, di acciaio, di lega futuristica o altro. In base al tipo, cambiano i tre bonus soprastanti forniti al pg

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int SlotMod;   //quanti slot per mod ha

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArmorStat")
		int SlotLevel;  //eventuale livello degli slot

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
};
