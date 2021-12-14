 // Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterState.h"
#include "UObject/ConstructorHelpers.h"

UCharacterState::UCharacterState()
{
	CurrentHealth = 1;
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

void UCharacterState::Init()
{
	CurrentHealth = Health;
}

void UCharacterState::IncreaseActionPoints(int Points)
{
	CurrentActionPoints += Points;
	CurrentActionPoints = FMath::Min(2, CurrentActionPoints);
	BroadcastChangedAP();
}

void UCharacterState::DecreaseActionPoints(int Points)
{
	CurrentActionPoints -= Points;
	CurrentActionPoints = FMath::Max(0, CurrentActionPoints);
	BroadcastChangedAP();

}
