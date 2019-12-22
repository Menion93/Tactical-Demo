// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TacticalGameGameMode.h"
#include "TacticalGamePlayerController.h"
#include "TacticalGameCharacter.h"
#include "BattleGameState.h"
#include "UObject/ConstructorHelpers.h"

ATacticalGameGameMode::ATacticalGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATacticalGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		GameStateClass = ABattleGameState::StaticClass();
	}

}

void ATacticalGameGameMode::Tick(float DeltaSeconds)
{
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