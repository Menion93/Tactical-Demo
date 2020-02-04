// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponCore.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UWeaponCore : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponCore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int BulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int BulletPerRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int Tier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int FireRate;  // Round per Action

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int ReloadCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int Accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int OptimalDamageDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int CriticalDamage;  //moltiplicatore del danno critico

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int CriticalChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int Magazine;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
