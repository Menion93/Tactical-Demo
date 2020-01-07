// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterState.h"
#include "UObject/ConstructorHelpers.h"

UCharacterState::UCharacterState()
{

}

void UCharacterState::Init(FString BPClassName)
{
	ActorCharacterClass = ConstructorHelpersInternal::FindOrLoadClass(BPClassName, AControllableCharacter::StaticClass());
}