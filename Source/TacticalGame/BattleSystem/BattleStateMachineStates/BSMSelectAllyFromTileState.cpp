// Fill out your copyright notice in the Description page of Project Settings.
#include "BSMSelectAllyFromTileState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "BattleSystem/BattleManager.h"
#include "TopViewCamera.h"


bool UBSMSelectAllyFromTileState::InputEventA(float DeltaTime)
{
	TArray<UObject*> SupportOptions = StateMachine->CurrentCharacter->GetSupportOptions();

	StateMachine->SupportOptions = SupportOptions
		.FilterByPredicate([this](auto& Object) {
		IActionable* SupportOption = Cast<IActionable>(Object);
		return SupportOption->Execute_IsInRangeFromTile(
			Object,
			this->BattleManager->GetSelectedTile(),
			this->StateMachine->CurrentCharacter,
			this->StateMachine->TargetCharacter);
	}
	);

	StateMachine->TransitionToState(CombatStateE::SELECT_SUPPORT_ACTION);
	return true;
}

