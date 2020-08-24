// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
#include "BattleSystem/Actions/MeleeAttackAction.h"
#include "Utils/SimStructs.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */

class AMeleeWeaponActor;

UCLASS()
class TACTICALGAME_API UMeleeWeapon : public UWeaponCore
{
	GENERATED_BODY()

public:
	UMeleeWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int AttacksPerTurn;

		// BULLET DAMAGE PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float Damage;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
		float DamageRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float MinRollDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float MaxRollDamage;

	// ACCURACY PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float BaseAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float Accuracy;

	UPROPERTY(BlueprintReadWrite, Category = "Accuracy")
		float AccuracyRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float MinAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float MaxAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float MinRollAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float MaxRollAccuracy;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FRoundSim> AttackSimulation;

	UPROPERTY(BlueprintReadWrite)
	UMeleeAttackAction* CurrentAction;

	UPROPERTY(BlueprintReadWrite)
	AMeleeWeaponActor* MeleeWeaponActor;


public:
	virtual bool IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target) override;
	virtual bool IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target) override;

	virtual void SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target) override;
	virtual void ApplyAction_Implementation(AGCharacter* Target) override;

	virtual UAction* GetAction_Implementation(AGCharacter* Subject, AGCharacter* Target, FTileIndex FromTile) override;

public:
	float GetAccuracy();
	float GetDamage();

	virtual void InitWeapon() override;
	void SpawnWeaponActor(AGCharacter* Character) override;


};
