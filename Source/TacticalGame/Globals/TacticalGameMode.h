// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleSystem/BattleManager.h"
#include "Characters/CharacterState.h"
#include "TopViewCamera.h"
#include "Blueprint/UserWidget.h"
#include "UI/BattleUI.h"
#include "Globals/GPlayerController.h"
#include "TacticalGameMode.generated.h"

class AGrid;

UENUM(BlueprintType)
enum class GameModeE : uint8
{
	GSE_Battle 	UMETA(DisplayName = "Battle"),
	GSE_None UMETA(DisplayName = "None"),
};

UCLASS(minimalapi)
class ATacticalGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ATacticalGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	GameModeE CurrentMode;

	UPROPERTY(BlueprintReadWrite)
	ATopViewCamera* Camera;

	UPROPERTY(BlueprintReadWrite)
	ABattleManager* BattleManager;

	UPROPERTY(BlueprintReadWrite)
	AGrid* Grid;

	UPROPERTY(BlueprintReadWrite)
	UBattleUI* BattleUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BattleModeOnLoad;

	AGPlayerController* Input;
	
private:
	void SetCamera();
	void SetGrid();
	void SetBattleManager();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void StartPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SwitchToBattleMode(bool IsPlayerTurn, bool ForceEngage);


	UFUNCTION(BlueprintImplementableEvent)
	void InitializeUI();

};