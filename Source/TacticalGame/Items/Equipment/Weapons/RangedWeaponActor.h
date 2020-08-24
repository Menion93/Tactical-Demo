// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment/Weapons/Weapon.h"
#include "Items/Equipment/Weapons/RangedWeapon.h"
#include "Characters/GCharacter.h"
#include "RangedWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API ARangedWeaponActor : public AWeapon
{
	GENERATED_BODY()
	
public:
	ARangedWeaponActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Simulation")
	int FireRate = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URangedWeapon* State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenBullets = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BulletsPerRound = 1;

private:
	int BulletIndex;
	int BulletFired;

	int IsFiring;
	bool FirstHit = true;

	float ElapsedTimeBetweenBullets;

public:

	UFUNCTION(BlueprintCallable)
	void Init(URangedWeapon* MyState);

	virtual void Tick(float DeltaTime) override;
	virtual void ExecuteAttack() override;

};
