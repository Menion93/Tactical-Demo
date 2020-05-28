// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
#include "BattleSystem/Actions/Actionable.h"
#include "Items/Equipment/Bag.h"
#include "Items/Equipment/Armor.h"
#include "Items/Equipment/Shield.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UEquipment : public UObject
{
	GENERATED_BODY()

public:
	UEquipment();
	
	// DEFAULTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWeaponCore> PrimaryWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWeaponCore> SecondaryWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBag> BagClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UArmor> ArmorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UShield> ShieldClass;

public:
	UPROPERTY(BlueprintReadWrite)
	UWeaponCore* PrimaryWeapon;

	UPROPERTY(BlueprintReadWrite)
	UWeaponCore* SecondaryWeapon;

	UPROPERTY(BlueprintReadWrite)
	UBag* Bag;

	UPROPERTY(BlueprintReadWrite)
	UArmor* Armor;

	UPROPERTY(BlueprintReadWrite)
	UShield* Shield;

public:

	// This method spawn all the default equipment
	UFUNCTION(BlueprintCallable)
	void LoadDefaultEquipment(AGCharacter* Owner);

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetOffensiveItems();

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetSupportItems();

private:
	UObject* TryGetObjectByType(UItem* Item, ActionType Type);


};
