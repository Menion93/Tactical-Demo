// Fill out your copyright notice in the Description page of Project Settings.

#include "Globals/TacticalGameGameMode.h"
#include "BSMCharacterInfoState.h"


UBSMCharacterInfoState::UBSMCharacterInfoState()
{

}

void UBSMCharacterInfoState::InputEventB()
{
	BattleManager->GameMode->BattleUI->CloseBag();
	BattleManager->CurrentState = CombatStateE::CHARACTER_SELECTED;
}
