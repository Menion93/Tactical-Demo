// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Party/Party.h"
#include "ActionMenuUI.h"
#include "BattleUI.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TACTICALGAME_API UBattleUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UActionMenuUI* ActionMenu;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParty* Party;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenActionMenu(const TArray<UBattleMenuItem*>& MenuItems);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenBag();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterBar(UPARAM(DisplayName = "CharacterState") UCharacterState* State);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideCharacterBar();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseBag();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseActionMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenAttackMenu(const TArray<UObject*>& OffensiveOptions);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseAttackMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenSupportOptionMenu(const TArray<UObject*>& SupportOptions);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseSupportOptionMenu();
		
};