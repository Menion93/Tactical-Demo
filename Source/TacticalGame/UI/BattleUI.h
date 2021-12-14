// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHealthBar.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterHealthBar* CharBar1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterHealthBar* CharBar2;

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenActionMenu(const TArray<UBattleMenuItem*>& MenuItems);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterBar1(UPARAM(DisplayName = "CharacterState") UCharacterState* State);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterBar2(UPARAM(DisplayName = "CharacterState") UCharacterState* State);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideCharacterBar1();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideCharacterBar2();

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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowOnTurnEnd(bool Show);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowOnBattleEnd(bool Show, bool Victory);
		
};