// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Equipment/Weapons/WeaponCore.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UMeleeWeapon : public UWeaponCore
{
	GENERATED_BODY()

public:
	UMeleeWeapon();

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

	TArray<FTileIndex> Directions;

public:
	virtual bool IsInRange(AGCharacter* MyCharacter, AGCharacter* Target) override;
	virtual bool IsInRangeFromCurrentPosition(AGCharacter* MyCharacter, AGCharacter* Target);

	virtual void SimulateAttack(AGCharacter* Character, AGCharacter* Target) override;
	virtual void ApplyAttack(AGCharacter* Target) override;

private:
	bool IsInRangeFromTile(FTile Tile, AGCharacter* Target);

	bool CanAttackEnemy_Implementation(AGCharacter* Character, AGCharacter* Target) override;
};
