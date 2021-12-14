// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UCharacterHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RefreshActionPoint();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayDamageAnimation();

	
};
