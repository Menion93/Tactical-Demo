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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init(ABattleManager* BM);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool PlayAction(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool RevertAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanExecuteAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnd();

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventX(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventY(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventA(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventB(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventStart(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventPause(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventR1(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventR2(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventL1(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventL2(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventLAxis(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventRAxis(float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent)
	bool InputEventPadUpDown(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	bool InputEventPadLeftRight(float DeltaTime);

};
