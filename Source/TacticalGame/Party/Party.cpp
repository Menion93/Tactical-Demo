// Fill out your copyright notice in the Description page of Project Settings.


#include "Party.h"

UParty::UParty()
{

}

void UParty::Init()
{
	UCharacterState* cs1 = NewObject<UCharacterState>(this, TEXT("cs1"));
	cs1->Init(TEXT("/Game/TopDownCPP/Blueprints/Characters/Player1"), TEXT("player1"));

	UCharacterState* cs2 = NewObject<UCharacterState>(this, TEXT("cs2"));
	cs2->Init(TEXT("/Game/TopDownCPP/Blueprints/Characters/Player2"), TEXT("player2"));

	TArray<UCharacterState*> team1;

	team1.Add(cs1);
	team1.Add(cs2);

	Teams2Characters.Emplace(0, team1);
}

TArray<UCharacterState*> UParty::GetSelectedTeam()
{
	return Teams2Characters[SelectedTeam];
}

void UParty::HandlePlayerInput()
{
	Teams2Characters[SelectedTeam][0]->ActorCharacter->HandleInput();
}

UCharacterState* UParty::GetCurrentLeader()
{
	return Teams2Characters[SelectedTeam][0];
}