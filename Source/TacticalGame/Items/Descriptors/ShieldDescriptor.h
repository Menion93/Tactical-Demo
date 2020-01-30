// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShieldDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UShieldDescriptor : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldStat")
		int BonusShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldStat")
		int BonusHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldStat")
		char ShieldType;

};
