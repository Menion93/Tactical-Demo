// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/GCharacterAnimInstance.h"
#include "Characters/CharacterState.h"
#include "Characters/GCharacter.h"


UGCharacterAnimInstance::UGCharacterAnimInstance()
{

}

void UGCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		AGCharacter* OwningChar = Cast<AGCharacter>(OwningActor);

		if (OwningChar != nullptr)
		{
			Speed = OwningChar->GetVelocity().Size();
			IsMoving = OwningChar->IsMoving;
			Shoot = OwningChar->Shooting;

			UCharacterState* State = OwningChar->State;

			if (State != nullptr)
			{
				Dead = OwningChar->State->CurrentHealth <= 0;

				UEquipment* Equipment = OwningChar->State->Equipment;

				if (Equipment != nullptr && OwningChar->State->Equipment->CurrentWeapon != nullptr)
				{
					RangedWeaponEquipped = OwningChar->State->Equipment->CurrentWeapon->IsRanged();
				}
			}


		}
	}
}

void UGCharacterAnimInstance::NativeBeginPlay()
{
	IsMoving = false;
	Shoot = false;
	Speed = 0;
}


void UGCharacterAnimInstance::PlayAttack()
{
	Montage_Play(PlayAttackMontage, 1, EMontagePlayReturnType::MontageLength, 0);
}

void UGCharacterAnimInstance::PlayMeleeAttack()
{
	Montage_Play(PlayMeleeAttackMontage, 1, EMontagePlayReturnType::MontageLength, 0);
}

void UGCharacterAnimInstance::PlayOnHit()
{
	Montage_Play(PlayOnHitMontage, OnHitPlayRate, EMontagePlayReturnType::MontageLength, 0);
}