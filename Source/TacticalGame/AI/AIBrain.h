// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleSystem/Actions/Action.h"
#include "Characters/GCharacter.h"
#include "AIBrain.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TACTICALGAME_API UAIBrain : public UObject
{
	GENERATED_BODY()

public:
	UAIBrain();

	UPROPERTY(BlueprintReadWrite)
	ATacticalGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Owner;

	UPROPERTY(BlueprintReadWrite) 
	AGCharacter * Target;

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UAction* GetAction();

	UFUNCTION(BlueprintNativeEvent)
	void Init(AGCharacter* mOwner, ATacticalGameMode* GM);
};
