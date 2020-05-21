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

	UPROPERTY(BlueprintReadWrite)
	URangedWeapon* State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MuzzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenBullets = 0.1;


private:
	int BulletIndex;
	int BulletFired;

	int IsFiring;
	bool FirstHit = true;

	float ElapsedTimeBetweenBullets;

	float TotalDamage = 0;

	TArray<FBulletSim> Round;
	AGCharacter* Target;

public:

	UFUNCTION(BlueprintCallable)
	void FireRound(TArray<FBulletSim> MyRound, AGCharacter* Target);

	virtual void Tick(float DeltaTime) override;
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


};
