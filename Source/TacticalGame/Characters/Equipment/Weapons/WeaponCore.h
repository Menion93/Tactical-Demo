// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Characters/GCharacter.h"
#include "Utils/Structs.h"
#include "Interfaces/OffensiveOption.h"
#include "WeaponCore.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UWeaponCore : public UItem, public IOffensiveOption
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponCore();

	// WEAPON MAIN PROPERTIES
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

public:
	virtual bool IsInRange(AGCharacter* MyCharacter, AGCharacter* Target);
	virtual bool IsInRangeFromCurrentPosition(AGCharacter* MyCharacter, AGCharacter* Target);

	virtual void SimulateAttack(AGCharacter* Character, AGCharacter* Target);
	virtual void ApplyAttack(AGCharacter* Target);
	virtual void Attack(AGCharacter* Character, AGCharacter* Target);

	virtual bool CanAttackEnemy_Implementation(AGCharacter* Character, AGCharacter* Target) override;

};
