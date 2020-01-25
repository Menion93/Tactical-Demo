// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ControllableCharacter.h"
#include "GameDirector.h"
#include "Inventory.h"
#include "BattleManager.h"
#include "CharacterState.h"
#include "Party.h"
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

	UPROPERTY()
	GameModeE CurrentMode;

	UPROPERTY()
	UGameDirector* GameDirector;

	UPROPERTY()
	UParty* Party;

	UPROPERTY()
	UInventory* Inventory;

	UPROPERTY()
	UBattleManager* BattleManager;
	

public:
	virtual void Tick(float DeltaTime) override;
	virtual void StartPlay() override;

	void SwitchToBattleMode(bool IsPlayerTurn);

};