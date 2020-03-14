// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/ControllableCharacter.h"
#include "Globals/GameDirector.h"
#include "Items/Inventory.h"
#include "BattleSystem/BattleManager.h"
#include "Characters/CharacterState.h"
#include "Party/Party.h"
#include "Blueprint/UserWidget.h"
#include "UI/BattleUI.h"
#include "Globals/GPlayerController.h"
#include "TacticalGameGameMode.generated.h"


UENUM(BlueprintType)
enum class GameModeE : uint8
{
	GSE_Battle 	UMETA(DisplayName = "Battle"),
	GSE_None UMETA(DisplayName = "None"),
};

UCLASS(minimalapi)
class ATacticalGameGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ATacticalGameGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	GameModeE CurrentMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameDirector* GameDirector;

	UPROPERTY(BlueprintReadWrite)
	UParty* Party;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UParty> PartyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBattleManager* BattleManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBattleUI* BattleUI;

	AGPlayerController* Input;
	

public:
	virtual void Tick(float DeltaTime) override;
	virtual void StartPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SwitchToBattleMode(bool IsPlayerTurn, bool ForceEngage);

	UFUNCTION(BlueprintCallable)
	void SwitchToFreeMode();

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeUI();

};