// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
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

public:
	virtual bool IsInRange_Implementation(AGCharacter* MyCharacter, AGCharacter* Target) override;
	virtual bool IsInRangeFromTile_Implementation(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target) override;

	virtual void SimulateAction_Implementation(AGCharacter* Character, AGCharacter* Target) override;
	virtual void ApplyAction_Implementation(AGCharacter* Target) override;

	virtual UAction* GetAction_Implementation() override;

};
