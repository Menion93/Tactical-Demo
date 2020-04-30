// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMSelectEnemyFromTileState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "BattleSystem/BattleManager.h"
#include "TopViewCamera.h"


bool UBSMSelectEnemyFromTileState::InputEventA(float DeltaTime)
{
	TArray<UObject*> OffensiveOptions = StateMachine->CurrentCharacter->GetOffensiveOptions();

	StateMachine->Actionables = OffensiveOptions
		.FilterByPredicate([this](auto& Object) {
		IActionable* OffensiveOption = Cast<IActionable>(Object);
		return OffensiveOption->Execute_IsInRangeFromTile(
			Object,
			this->BattleManager->GetSelectedTile(),
			this->StateMachine->CurrentCharacter,
			this->StateMachine->TargetCharacter);
	}
	);

	StateMachine->TransitionToState(CombatStateE::SELECT_ATTACK);
	return true;
}


