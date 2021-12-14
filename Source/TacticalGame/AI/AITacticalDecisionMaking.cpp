// Fill out your copyright notice in the Description page of Project Settings.


#include "AITacticalDecisionMaking.h"
#include "BattleSystem/AIFireTeam.h"
#include "TacticalAIComponent.h"

//UAITacticalDecisionMaking::UAITacticalDecisionMaking() {}

void UAITacticalDecisionMaking::Init(ABattleManager* MyBattleManager)
{
	BattleManager = MyBattleManager;
}


UAction* UAITacticalDecisionMaking::GenerateNextAction_Implementation(AAIFireTeam* FT)
{

	if (CurrentCharacter == nullptr)
	{
		CurrentCharacter = GetNextAICharacter(FT);
	}

	UTacticalAIComponent* AIComp = Cast<UTacticalAIComponent>(CurrentCharacter->GetComponentByClass(UTacticalAIComponent::StaticClass()));

	return AIComp->GetAction();
}
