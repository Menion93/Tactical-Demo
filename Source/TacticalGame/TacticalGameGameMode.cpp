// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TacticalGameGameMode.h"
#include "BattleGameState.h"
#include "Engine/World.h"
#include "ControllableCharacter.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GPlayerController.h"


ATacticalGameGameMode::ATacticalGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	GameStateClass = ABattleGameState::StaticClass();
	// Failsafe
	PlayerControllerClass = AGPlayerController::StaticClass();
	DefaultPawnClass = nullptr;

	GameDirector = NewObject<UGameDirector>(this, TEXT("GameDirector"));
}


void ATacticalGameGameMode::StartPlay()
{
	Super::StartPlay();
	GameDirector->Init();
	BState = GetGameState<ABattleGameState>();
	SwitchToBattleMode(true);
}

void ATacticalGameGameMode::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (CurrentMode == GameModeE::GSE_Battle)
	{
		BState->PlayTurn();
	}
}

void ATacticalGameGameMode::SwitchToBattleMode(bool IsPlayerTurn)
{
	CurrentMode = GameModeE::GSE_Battle;
	BState->InitBattleState(IsPlayerTurn);
}