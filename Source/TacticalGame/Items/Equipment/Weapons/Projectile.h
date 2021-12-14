// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BattleSystem/Actions/RangedAttackAction.h"
#include "Components/SphereComponent.h"
#include "Utils/SimStructs.h"
#include "Projectile.generated.h"

class AGCharacter;

UCLASS()
class TACTICALGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	FRoundSim RoundSim;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Target;

	UPROPERTY(BlueprintReadWrite)
	URangedAttackAction* Action;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);
	void EnableRegisterDamageEvent(AGCharacter* MyTarget, FRoundSim MyRoundSim, URangedAttackAction* Action);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);



};
