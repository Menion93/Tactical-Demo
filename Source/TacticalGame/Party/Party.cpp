// Fill out your copyright notice in the Description page of Project Settings.


#include "Party.h"

UParty::UParty()
{

}

void UParty::Init()
{
	for (auto& Pair : Teams2ActorBPClass)
	{
		FCharacterStateArray Team;

		for (auto& Elem : Pair.Value.Array)
		{
			UCharacterState* Char = NewObject<UCharacterState>(this);
			Char->ActorCharacterClass = Elem;

			Team.Array.Add(Char);
		}

		Teams2Characters.Emplace(Pair.Key, Team);
	}
}

TArray<UCharacterState*> UParty::GetSelectedTeam()
{
	return Teams2Characters[SelectedTeam].Array;
}

void UParty::HandlePlayerInput()
{
	Teams2Characters[SelectedTeam].Array[0]->ActorCharacter->HandleInput();
}

UCharacterState* UParty::GetCurrentLeader()
{
	return Teams2Characters[SelectedTeam].Array[0];
}