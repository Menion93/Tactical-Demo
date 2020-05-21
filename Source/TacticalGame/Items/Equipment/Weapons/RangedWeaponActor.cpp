// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeaponActor.h"

ARangedWeaponActor::ARangedWeaponActor()
{
	OnActorHit.AddDynamic(this, &ARangedWeaponActor::OnHit);

}

void ARangedWeaponActor::FireRound(TArray<FBulletSim> MyRound, AGCharacter* MyTarget)
{
	URangedWeapon* State = Cast<URangedWeapon>(WeaponCore);
	Target = MyTarget;
	Round = MyRound;
	IsFiring = true;
	FirstHit = true;
	//TotalDamage = 0;


	//for (auto& BulletSim : Round)
	//{
	//	TotalDamage += BulletSim.Damage;
	//}
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
					Projectile->EnableRegisterDamageEvent(TotalDamage);
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
		}
		
	}

}

void ARangedWeaponActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AGCharacter* CharacterHit = Cast<AGCharacter>(OtherActor);

	if (CharacterHit)
	{
		// Notify Character Was Hit and Took Damage
		CharacterHit->TakeRangedWeaponDamage(Round);
	}
}
