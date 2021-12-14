 // Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystem/AIFireTeam.h"
#include "BattleSystem/BattleManager.h"



void AAIFireTeam::Init_Implementation(ABattleManager* BM)
{
	Super::Init_Implementation(BM);

	if (TacticalAIClass)
	{
		TacticalAI = NewObject<UAITacticalDecisionMaking>(this, TacticalAIClass);
		TacticalAI->Init(BattleManager);
	}
	CurrentAction = nullptr;
}


void AAIFireTeam::PlayTurn_Implementation(float DeltaTime)
{
	if (CurrentAction == nullptr || BattleManager->GetAction() == nullptr)
	{
		CurrentAction = TacticalAI->GenerateNextAction(this);
		CurrentCharacter = TacticalAI->CurrentCharacter;
		BattleManager->SetAction(CurrentAction);
	}
}


void AAIFireTeam::OnTurnStart_Implementation()
{
	Super::OnTurnStart_Implementation();

	for (auto Char : Characters)
	{
		if (Char->State->CurrentHealth > 0)
		{
			// reset action points
			Char->State->ResetActionPoints();
		}
	}
}