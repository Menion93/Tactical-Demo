// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Party/Party.h"
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
	UParty* Party;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenActionMenu(
		AControllableCharacter* CurrentCharacter,
		AGCharacter* CharacterInTile,
		FTile Tile);

	UFUNCTION(BlueprintImplementableEvent)
	void OpenBag();

	
	UFUNCTION(BlueprintImplementableEvent)
	void SetCharacterBar(UPARAM(DisplayName = "CharacterState") UCharacterState* State);

	UFUNCTION(BlueprintImplementableEvent)
	void HideCharacterBar();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseBag();



	
};
