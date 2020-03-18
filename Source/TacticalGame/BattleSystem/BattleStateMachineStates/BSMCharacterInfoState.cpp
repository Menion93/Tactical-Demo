// Fill out your copyright notice in the Description page of Project Settings.

#include "BSMCharacterInfoState.h"
#include "Globals/TacticalGameGameMode.h"


UBSMCharacterInfoState::UBSMCharacterInfoState()
{

}

void UBSMCharacterInfoState::InputEventB()
{
	BattleManager->GameMode->BattleUI->CloseBag();
	BattleManager->TransitionToState(CombatStateE::CHARACTER_SELECTED);
}
