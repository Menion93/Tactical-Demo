// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TacticalGameGameMode.h"
#include "Engine/World.h"
#include "Characters/ControllableCharacter.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GPlayerController.h"
#include "Characters/CharacterState.h"


ATacticalGameGameMode::ATacticalGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = AGPlayerController::StaticClass();
	DefaultPawnClass = nullptr;

	GameDirector = NewObject<UGameDirector>(this, TEXT("GameDirector"));

	Party = NewObject<UParty>(this, TEXT("Party"));
	Party->Init();
}


void ATacticalGameGameMode::StartPlay()
{
	Super::StartPlay();

	GameDirector->Init();
	GameDirector->SpawnCharacters(true);

	BattleManager = NewObject<UBattleManager>(this, TEXT("BattleManager"));
	BattleManager->Init();
	SwitchToBattleMode(true);

}

void ATacticalGameGameMode::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (CurrentMode == GameModeE::GSE_Battle)
	{
		BattleManager->PlayTurn();
	}
}

void ATacticalGameGameMode::SwitchToBattleMode(bool IsPlayerTurn)
{
	CurrentMode = GameModeE::GSE_Battle;
	BattleManager->InitBattleState(IsPlayerTurn);
}