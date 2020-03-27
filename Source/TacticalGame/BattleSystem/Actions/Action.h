// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Globals/GPlayerController.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReversibleAction;

public:

	void Init(ABattleManager* BM);

	UFUNCTION(BlueprintNativeEvent)
	bool PlayAction();

	UFUNCTION(BlueprintNativeEvent)
	void ReverseAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanExecuteAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnd();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventX();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventY();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventA();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventB();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventStart();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventPause();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventR1();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventR2();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventL1();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventL2();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventLAxis();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventRAxis();
	
	UFUNCTION(BlueprintNativeEvent)
	void InputEventPadUpDown();

	UFUNCTION(BlueprintNativeEvent)
	void InputEventPadLeftRight();

};
