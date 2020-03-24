// Fill out your copyright notice in the Description page of Project Settings.


#include "Party.h"

UParty::UParty()
{

}

void UParty::Init()
{
	for (auto& CharClass : CharactersClasses)
	{
		UCharacterState* Char = NewObject<UCharacterState>(
			this, CharClass->GetFName(), RF_NoFlags, CharClass.GetDefaultObject());

		Char->LoadState();
		Characters.Add(Char);
	}

	for (auto& index : TeamIndexes)
	{
		if (index < Characters.Num())
		{
			Team.Add(Characters[index]);
		}
	}
}

TArray<UCharacterState*> UParty::GetTeam()
{
	return Team;
}

void UParty::HandlePlayerInput()
{
	Team[0]->ActorCharacter->HandleInput();
}

UCharacterState* UParty::GetCurrentLeader()
{
	return Team[0];
}