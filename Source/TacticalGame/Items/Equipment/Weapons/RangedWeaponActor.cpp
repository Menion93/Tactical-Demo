// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"


ARangedWeaponActor::ARangedWeaponActor()
{

}


// Called every frame
void ARangedWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFiring)
	{
		ElapsedTimeBetweenBullets += DeltaTime;
		if (BulletIndex < Round.BulletsFired)
		{
			if (ElapsedTimeBetweenBullets >= TimeBetweenBullets)
			{
				ElapsedTimeBetweenBullets = 0;

				FVector MuzzleLocation = MeshComp->GetSocketLocation(FName("FireSocket"));

				AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(State->ProjectileClass, MuzzleLocation, MuzzleLocation.ToOrientationRotator());

				FVector Direction = Target->GetActorLocation() - Projectile->GetActorLocation();
				Direction.Normalize();

				if (FirstHit)
				{
					Projectile->EnableRegisterDamageEvent(Target, Round, State->CurrentAction);
					FirstHit = false;
				}

				if (Round.HasHit)
				{
					// Spawn a projectile that will hit the target
					if (Projectile)
					{
						Projectile->FireInDirection(Direction);
					}

				}
				else
				{
					// Spawn a projectile that will not hit the target
					if (Projectile)
					{
						Projectile->FireInDirection(Direction);
					}
				}
				State->OnProjectileShoot.Broadcast();

				// Add Cooldown
				BulletIndex += 1;
			}

		}
		else
		{
			IsFiring = false;
			ElapsedTimeBetweenBullets = 0;

			// All bullets in round missed
			if (!FirstHit)
			{
				// With a timer
			}
		}
	}

}

void ARangedWeaponActor::ExecuteAttack()
{
	IsFiring = true;
	FirstHit = true;
	BulletIndex = 0;
	State->CurrentAmmo -= Round.BulletsFired;
}

void ARangedWeaponActor::Init(URangedWeapon* MyState)
{
	State = MyState;
}
