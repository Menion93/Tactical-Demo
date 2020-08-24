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
	// Use defaults for first time or force, or else load from file
	LoadDefaultState();
	// Load from file method
}

void UCharacterState::LoadDefaultState()
{
	Equipment = NewObject<UEquipment>(this, EquipmentClass);
	Equipment->LoadDefaultEquipment(this);
}