// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleStateMachine.h"

UBattleStateMachine::UBattleStateMachine()
{
	State2Method.Emplace(CombatStateE::DESELECTED_STATE, &UBattleStateMachine::DeselectedState);
	State2Method.Emplace(CombatStateE::CHARACTER_SELECTED, &UBattleStateMachine::CharacterSelected);
	State2Method.Emplace(CombatStateE::ENEMY_LOCKED, &UBattleStateMachine::EnemyLocked);
	State2Method.Emplace(CombatStateE::TILE_SELECTED, &UBattleStateMachine::TileSelected);
}

UAction* UBattleStateMachine::DeselectedState()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	UE_LOG(LogTemp, Warning, TEXT("DeselectedState state"));
	return action;
}

UAction* UBattleStateMachine::CharacterSelected()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	UE_LOG(LogTemp, Warning, TEXT("CharacterSelected state"));
	return action;
}

UAction* UBattleStateMachine::EnemyLocked()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	UE_LOG(LogTemp, Warning, TEXT("EnemyLocked state"));
	return action;
}

UAction* UBattleStateMachine::TileSelected()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	UE_LOG(LogTemp, Warning, TEXT("TileSelected state"));
	return action;
}

UAction* UBattleStateMachine::PlayState()
{
	return (this->* (State2Method[CurrentState]))();
}

void UBattleStateMachine::Reset()
{
	CurrentState = CombatStateE::DESELECTED_STATE;
}