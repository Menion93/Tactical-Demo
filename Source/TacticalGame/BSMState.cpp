// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMState.h"
#include "TacticalGameGameMode.h"


UBSMState::UBSMState() {}

void UBSMState::Init()
{
	ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		TileMap = GameMode->GameDirector->TileMap;
	}

	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());

	BattleManager = GameMode->BattleManager;

}

UAction* UBSMState::PlayState()
{
	return nullptr;
}