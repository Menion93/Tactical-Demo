// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterState.h"
#include "UObject/ConstructorHelpers.h"

UCharacterState::UCharacterState()
{
	CurrentHealth = 100;
}

void UCharacterState::ResetActionPoints()
{
	CurrentActionPoints = ActionPoints;
}

void UCharacterState::LoadState()
{

}