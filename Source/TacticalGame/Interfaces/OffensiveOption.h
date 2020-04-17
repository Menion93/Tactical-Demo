// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OffensiveOption.generated.h"

class AGCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UOffensiveOption : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALGAME_API IOffensiveOption
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	FString GetName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	bool IsInRange(AGCharacter* MyCharacter, AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	bool IsInRangeFromTile(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	void SimulateAttack(AGCharacter* Character, AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	void ApplyAttack(AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Offensive Option")
	void Attack(AGCharacter* Character, AGCharacter* Target);
};
