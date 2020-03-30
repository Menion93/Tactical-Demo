// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TacticalGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GPlayerController.h"
#include "Components/DecalComponent.h"
#include "Grid/Grid.h"
#include "Characters/CharacterState.h"


ATacticalGameMode::ATacticalGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = AGPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}


void ATacticalGameMode::StartPlay()
{
	Super::StartPlay();
	SetCamera();
	SetGrid();
	SetBattleManager();

	if (PartyClass)
	{
		Party = NewObject<UParty>(this, PartyClass->GetFName(), RF_NoFlags, PartyClass.GetDefaultObject());
		Party->Init();
	}

	BattleManager->Init();

	if (BattleModeOnLoad)
	{
		SwitchToBattleMode(true, false);
	} 
	else
	{
		SwitchToFreeMode();
	}

	UWorld* World = GetWorld();

	if (World)
	{
		Input = Cast<AGPlayerController>(World->GetFirstPlayerController());
	}

	InitializeUI();
}

void ATacticalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Input)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			Input = Cast<AGPlayerController>(World->GetFirstPlayerController());
		}
	}

	if (CurrentMode == GameModeE::GSE_Battle)
	{
		BattleManager->PlayTurn();
	}
	else if (CurrentMode == GameModeE::GSE_None)
	{
		Party->HandlePlayerInput();
	}

	if (Camera)
	{
		Camera->Tick(DeltaSeconds);
	}

	if (Input->L2_DOWN)
	{
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

void ATacticalGameMode::SwitchToBattleMode(bool IsPlayerTurn, bool ForceEngage)
{
	// Here put Dynamic Grid Creation
	CurrentMode = GameModeE::GSE_Battle;
	Grid->GridCursor->SetVisibility(true);
	Camera->DetachFromActor();
	BattleManager->InitBattleState(IsPlayerTurn, ForceEngage);
}

void ATacticalGameMode::SwitchToFreeMode()
{
	// Here put Dynamic Grid Creation
	CurrentMode = GameModeE::GSE_None;
	Grid->GridCursor->SetVisibility(false);
	Camera->AttachToActor(Party->GetCurrentLeader()->ActorCharacter);
}

void ATacticalGameMode::SetGrid()
{
	AActor* TileTmp = UGameplayStatics::GetActorOfClass(GetWorld(), AGrid::StaticClass());

	if (TileTmp)
	{
		Grid = Cast<AGrid>(TileTmp);
	}
}


void ATacticalGameMode::SetCamera()
{
	AActor* CameraTmp = UGameplayStatics::GetActorOfClass(GetWorld(), ATopViewCamera::StaticClass());

	if (CameraTmp)
	{
		Camera = Cast<ATopViewCamera>(CameraTmp);
	}
}

void ATacticalGameMode::SetBattleManager()
{
	AActor* BattleManagerTmp = UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass());

	if (BattleManagerTmp)
	{
		BattleManager = Cast<ABattleManager>(BattleManagerTmp);
	}
}

