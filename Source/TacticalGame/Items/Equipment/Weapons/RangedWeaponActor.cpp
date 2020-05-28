// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeaponActor.h"

ARangedWeaponActor::ARangedWeaponActor()
{

}

void ARangedWeaponActor::FireRound(TArray<FBulletSim> MyRound, AGCharacter* MyTarget)
{
	State = Cast<URangedWeapon>(WeaponCore);
	Target = MyTarget;
	Round = MyRound;
	IsFiring = true;
	FirstHit = true;
}

// Called every frame
void ARangedWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFiring)
	{
		ElapsedTimeBetweenBullets += DeltaTime;
		if (BulletIndex < Round.Num() && ElapsedTimeBetweenBullets >= TimeBetweenBullets)
		{
			ElapsedTimeBetweenBullets = 0;

			FBulletSim BulletSim = Round[BulletIndex];

			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(State->ProjectileClass, MuzzleLocation, FRotator::ZeroRotator);

			if (BulletSim.HasHit)
			{
				// Spawn a projectile that will hit the target
				if (Projectile)
				{
					Projectile->FireInDirection(Target->GetActorLocation() - Projectile->GetActorLocation());
				}

				if (FirstHit)
				{
					Projectile->EnableRegisterDamageEvent(Target, Round);
				}
			}
			else
			{
				// Spawn a projectile that will not hit the target
				if (Projectile)
				{
					Projectile->FireInDirection(Target->GetActorLocation() - Projectile->GetActorLocation());
				}
			}

			// Add Cooldown
			BulletIndex += 1;

		}
		else
		{
			IsFiring = false;
			ElapsedTimeBetweenBullets = 0;
			State->CurrentAction->RoundFinished();
		}
	}

}

void ARangedWeaponActor::Init(URangedWeapon* MyState)
{
	State = MyState;
}
