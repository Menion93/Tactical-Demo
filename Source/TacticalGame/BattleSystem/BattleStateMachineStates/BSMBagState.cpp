// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMBagState.h"
#include "Globals/TacticalGameGameMode.h"

UBSMBagState::UBSMBagState()
{

}

void UBSMBagState::InputEventB()
{
	BattleManager->GameMode->BattleUI->CloseBag();
	BattleManager->TransitionToState(CombatStateE::CHARACTER_SELECTED);
}

void UBSMBagState::OnEnter()
{
	BattleManager->GameMode->BattleUI->OpenBag();
}