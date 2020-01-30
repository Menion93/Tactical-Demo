// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMTileSelectedState.h"

UBSMTileSelectedState::UBSMTileSelectedState(){}

UAction* UBSMTileSelectedState::PlayState()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));
	return action;

}