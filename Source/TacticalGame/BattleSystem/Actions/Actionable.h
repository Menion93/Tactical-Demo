// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleSystem/Actions/Action.h"
#include "Grid/FTile.h"
#include "Actionable.generated.h"

class AGCharacter;

UENUM(BlueprintType)
enum class ActionType : uint8
{
	OFFENSIVE UMETA(DisplayName = "Offensive Action"),
	SUPPORT UMETA(DisplayName = "Support Action"),
	BOTH UMETA(DisplayName = "Offensive&Support Action"),
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UActionable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALGAME_API IActionable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	FString GetMenuDisplayName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	bool IsInRange(AGCharacter* MyCharacter, AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	bool IsInRangeFromTile(FTile Tile, AGCharacter* MyCharacter, AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	void SimulateAction(AGCharacter* Character, AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	void ApplyAction(AGCharacter* Target);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	UAction* GetAction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actionable")
	ActionType GetActionType();
};
