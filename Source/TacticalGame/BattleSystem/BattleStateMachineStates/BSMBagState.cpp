// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMBagState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"

UBSMBagState::UBSMBagState()
{

}

bool UBSMBagState::InputEventB()
{
	BattleManager->GameMode->BattleUI->CloseBag();
	StateMachine->TransitionToState(CombatStateE::CHARACTER_SELECTED);
	return true;
}

void UBSMBagState::OnEnter()
{
	BattleManager->GameMode->BattleUI->OpenBag();
}