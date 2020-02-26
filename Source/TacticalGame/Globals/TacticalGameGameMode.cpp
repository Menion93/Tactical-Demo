// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TacticalGameGameMode.h"
#include "Engine/World.h"
#include "Characters/ControllableCharacter.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GPlayerController.h"
#include "Components/DecalComponent.h"
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
	SwitchToBattleMode(true, false);

	UWorld* World = GetWorld();

	if (World)
	{
		Input = Cast<AGPlayerController>(World->GetFirstPlayerController());
	}

	//SwitchToFreeMode();
}

void ATacticalGameGameMode::Tick(float DeltaSeconds)
{
	if (!Input)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			Input = Cast<AGPlayerController>(World->GetFirstPlayerController());
		}
	}


	Super::Tick(DeltaSeconds);

	if (CurrentMode == GameModeE::GSE_Battle)
	{
		BattleManager->PlayTurn();
	}
	else if(CurrentMode == GameModeE::GSE_None)
	{
		Party->HandlePlayerInput();
	}

	if (GameDirector->Camera)
	{
		GameDirector->Camera->Tick(DeltaSeconds);
	}

	if (!BattleManager->BattleEngaged && Input->R1_DOWN)
	{
		Input->R1_DOWN = false;

		if (CurrentMode == GameModeE::GSE_Battle)
		{
			SwitchToFreeMode();
		}
		else
		{
			SwitchToBattleMode(true, false);
		}
	}
}

void ATacticalGameGameMode::SwitchToBattleMode(bool IsPlayerTurn, bool ForceEngage)
{
	// Here put Dynamic Grid Creation
	CurrentMode = GameModeE::GSE_Battle;
	GameDirector->TileMap->GridCursor->SetVisibility(true);
	GameDirector->Camera->DetachFromActor();
	BattleManager->InitBattleState(IsPlayerTurn, ForceEngage);
}

void ATacticalGameGameMode::SwitchToFreeMode()
{
	// Here put Dynamic Grid Creation
	CurrentMode = GameModeE::GSE_None;
	GameDirector->TileMap->GridCursor->SetVisibility(false);
	GameDirector->Camera->AttachToActor(Party->GetCurrentLeader()->ActorCharacter);
}