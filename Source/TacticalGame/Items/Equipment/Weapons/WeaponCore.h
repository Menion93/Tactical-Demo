// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Characters/GCharacter.h"
#include "Utils/Structs.h"
#include "BattleSystem/Actions/Actionable.h"
#include "BattleSystem/Actions/Action.h"
#include "Weapon.h"
#include "BattleSystem/Actions/Action.h"
#include "WeaponCore.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UWeaponCore : public UItem, public IActionable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponCore();

	// WEAPON MAIN PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AWeapon> WeaponActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAction> ActionClass;

	UPROPERTY(BlueprintReadWrite)
	AWeapon* WeaponActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int Tier;

	// CRITICAL DAMAGE PROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Damage")
	float BaseCriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Damage")
	float CriticalDamage;

	UPROPERTY(BlueprintReadWrite, Category = "CriticalDamage")
	float CriticalDamageRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Damage")
	float MinCriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Damage")
	float MaxCriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Damage")
	float MinRollCriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Damage")
	float MaxRollCriticalDamage;

	 // CRITICAL CHANCE PROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Chance")
	float BaseCriticalChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Chance")
	float CriticalChance;

	UPROPERTY(BlueprintReadWrite, Category = "Critical Chance")
	float CriticalChanceRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Chance")
	float MinCriticalChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Chance")
	float MaxCriticalChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Chance")
	float MinRollCriticalChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Chance")
	float MaxRollCriticalChance;


public:
	FSimulationOutput Simulation;

	float GetCriticalDamage();
	float GetCriticalChance();

public:
	virtual FString GetMenuDisplayName_Implementation() override;

	virtual bool IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target);
	virtual bool IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target);

	virtual void SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target);
	virtual void ApplyAction_Implementation(AGCharacter* Target);

	virtual UAction* GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile);

	virtual ActionType GetActionType_Implementation();

	virtual void InitWeapon(AGCharacter* Character);


};
