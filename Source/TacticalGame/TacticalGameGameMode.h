// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

	virtual void Tick(float DeltaTime) override;
	void SwapGameState(AGameStateBase* GameStateVariable);


};



