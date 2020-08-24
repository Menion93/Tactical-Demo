// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment/Weapons/Weapon.h"
#include "MeleeWeapon.h"
#include "MeleeWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API AMeleeWeaponActor : public AWeapon
{
	GENERATED_BODY()
public:
	AMeleeWeaponActor();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMeleeWeapon* State;

	UFUNCTION(BlueprintCallable)
	void Init(UMeleeWeapon* MyState);

	virtual void ExecuteAttack() override;
	
};
