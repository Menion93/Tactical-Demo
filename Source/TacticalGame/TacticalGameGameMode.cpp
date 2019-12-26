// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TacticalGameGameMode.h"
#include "TacticalGamePlayerController.h"
#include "TacticalGameCharacter.h"
#include "BattleGameState.h"
#include "Engine/World.h"
#include "ControllableCharacter.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


ATacticalGameGameMode::ATacticalGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	GameStateClass = ABattleGameState::StaticClass();

	GameDirector = NewObject<UGameDirector>(this, TEXT("GameDirector"));
}


void ATacticalGameGameMode::StartPlay()
{
	Super::StartPlay();
	GameDirector->Init();
}

void ATacticalGameGameMode::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (CurrentMode == GameModeE::GSE_Battle)
	{
		ABattleGameState* BState = GetGameState<ABattleGameState>();

		BState->PlayTurn();
	}

}


void ATacticalGameGameMode::SwapGameState(AGameStateBase* GameStateVariable)
{
	GameStateClass = GameStateVariable->StaticClass();
}