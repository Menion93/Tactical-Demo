// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMUnitInfoState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"

UBSMUnitInfoState::UBSMUnitInfoState()
{

}

void UBSMUnitInfoState::OnEnter()
{
	Target = StateMachine->TargetCharacter;
	Tile = BattleManager->GetSelectedTile();
	// Open Unit Info Frame
}

bool UBSMUnitInfoState::InputEventB(float DeltaTime)
{
	BattleManager->GameMode->BattleUI->HideCharacterBar1();
	StateMachine->TargetCharacter = nullptr;
	StateMachine->TransitionToPrevState();
	// Close Unit Info Frame

	return true;
}


