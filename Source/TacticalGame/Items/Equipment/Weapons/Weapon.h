// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/SimStructs.h"
#include "Animation/AnimMontage.h"
#include "Weapon.generated.h"

class UWeaponCore;

UCLASS()
class TACTICALGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(BlueprintReadWrite)
	UWeaponCore* WeaponCore;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* WeaponAnimation;

	FRoundSim Round;

	AGCharacter* Target;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SnapToActor(AGCharacter* Character);

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteAttack();


	UFUNCTION(BlueprintCallable)
	virtual void SetSimulationInfo(FRoundSim MyRound, AGCharacter* Target);

};
