// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GCharacterAnimInstance.generated.h"

/**
 * 
 */

UCLASS()
class TACTICALGAME_API UGCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public: 
	UGCharacterAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OnHitPlayRate = 1.3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Dead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RangedWeaponEquipped = false;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* PlayAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* PlayMeleeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* PlayOnHitMontage;


public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlayAttack();

	UFUNCTION(BlueprintCallable)
	void PlayMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void PlayOnHit();

};
