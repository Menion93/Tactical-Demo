// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/GCharacter.h"
#include "Skill.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API USkill : public UObject
{
	GENERATED_BODY()


public:
	USkill();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	TArray<AGCharacter*> GetElegibleTargets();
};
