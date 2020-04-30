// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
#include "RangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API URangedWeapon : public UWeaponCore
{
	GENERATED_BODY()
	
public:
	URangedWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int ReloadCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int Magazine;

	// BULLET DAMAGE PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Damage")
		int BaseBulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Damage")
		float BulletDamage;

	UPROPERTY(BlueprintReadWrite, Category = "Bullet Damage")
		float BulletDamageRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Damage")
		float MinBulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Damage")
		float MaxBulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Damage")
		float MinRollBulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Damage")
		float MaxRollBulletDamage;

	// WEAPON ROUNDS PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rounds Stats")
		int Rounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rounds Stats")
		int BulletsPerRound;

	// ACCURACY AND RANGE PROPERTIES
	UPROPERTY(EditAnywhere, Category = "Accuracy")
	FRuntimeFloatCurve AccuracyByRange;

	UPROPERTY(BlueprintReadWrite, Category = "Accuracy")
		float AccuracyRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float MinRollAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
		float MaxRollAccuracy;

	// RANGE PROPERTIES
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
		int BaseRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
		int Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
		int RangeRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
		int MinRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
		int MaxRange;


public:
	virtual bool IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target) override;
	virtual bool IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target) override;

	virtual void SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target) override;
	virtual void ApplyAction_Implementation(AGCharacter* Target) override;

	virtual UAction* GetAction_Implementation() override;

	float GetRange();
};
