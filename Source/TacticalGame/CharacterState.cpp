// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterState.h"
#include "UObject/ConstructorHelpers.h"

UCharacterState::UCharacterState()
{
	CurrentHealth = 100;
}

void UCharacterState::Init(FString BPClassName, FName name)
{
	ActorCharacterClass = ConstructorHelpersInternal::FindOrLoadClass(BPClassName, AControllableCharacter::StaticClass());
	Name = name;
}