// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState(){}

UAction* UBSMCharacterSelectedState::PlayState()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	return action;

}