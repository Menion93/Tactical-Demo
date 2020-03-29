// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Globals/GPlayerController.h"
#include "Grid/FTile.h"
#include "Action.generated.h"

class ABattleManager;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TACTICALGAME_API UAction : public UObject
{
	GENERATED_BODY()

public:
	UAction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionName;

	UPROPERTY()
	AGPlayerController* Input;

	UPROPERTY(BlueprintReadWrite)
	ABattleManager* BattleManager;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Character;

	UPROPERTY(BlueprintReadWrite)
	AGCharacter* Target;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex FocusedTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReversibleAction;

public:

	UFUNCTION(BlueprintNativeEvent)
	void Init(ABattleManager* BM);

	UFUNCTION(BlueprintNativeEvent)
	bool PlayAction();

	UFUNCTION(BlueprintNativeEvent)
	void RevertAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanExecuteAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnd();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventX();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventY();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventA();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventB();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventStart();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventPause();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventR1();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventR2();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventL1();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventL2();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventLAxis();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventRAxis();
	
	UFUNCTION(BlueprintNativeEvent)
	bool InputEventPadUpDown();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventPadLeftRight();

};
