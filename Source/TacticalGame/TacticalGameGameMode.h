// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ControllableCharacter.h"
#include "GameDirector.h"
#include "Inventory.h"
#include "BattleGameState.h"
#include "CharacterState.h"
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
	GameModeE CurrentMode;
	UGameDirector* GameDirector;
	UInventory* Inventory;
	TArray<UCharacterState*> players;

	ABattleGameState* BState;
	

public:
	virtual void Tick(float DeltaTime) override;
	virtual void StartPlay() override;

	void SwitchToBattleMode(bool IsPlayerTurn);



};