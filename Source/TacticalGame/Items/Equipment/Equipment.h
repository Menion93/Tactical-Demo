// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
#include "BattleSystem/Actions/Actionable.h"
#include "Items/Equipment/Armor.h"
#include "Items/Equipment/Shield.h"
#include "Equipment.generated.h"

class UCharacterState;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwapWeapon);

UCLASS(Blueprintable)
class TACTICALGAME_API UEquipment : public UObject
{
	GENERATED_BODY()

public:
	UEquipment();

	UCharacterState* State;

	// DEFAULTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWeaponCore> PrimaryWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWeaponCore> SecondaryWeaponClass;

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
	UArmor* Armor;

	UPROPERTY(BlueprintReadWrite)
	UShield* Shield;

	UPROPERTY(BlueprintReadWrite)
	UWeaponCore* CurrentWeapon;

	UPROPERTY(BlueprintAssignable)
	FOnSwapWeapon OnSwapWeapon;

private:
	bool FirstWeaponEquipped = true;

public:

	// This method spawn all the default equipment
	UFUNCTION(BlueprintCallable)
	void LoadDefaultEquipment(UCharacterState* State);

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetOffensiveItems();

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetSupportItems();

	UFUNCTION(BlueprintCallable)
	void SwapWeapon();

	UFUNCTION(BlueprintCallable)
	void SpawnWeaponActor();

private:
	UObject* TryGetObjectByType(UItem* Item, ActionType Type);


};
