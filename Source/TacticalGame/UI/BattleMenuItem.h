// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleSystem/BattleManager.h"
#include "BattleMenuItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UBattleMenuItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	ABattleManager* BattleManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MenuItemName;

public:

	void Init(ABattleManager* BM);

	UFUNCTION(BlueprintNativeEvent)
	bool ShowMenuOption();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOptionSelected();

};
