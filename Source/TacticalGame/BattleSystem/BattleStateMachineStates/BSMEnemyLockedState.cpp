// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMEnemyLockedState.h"

UBSMEnemyLockedState::UBSMEnemyLockedState(){}

UAction* UBSMEnemyLockedState::PlayState()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	return action;

}