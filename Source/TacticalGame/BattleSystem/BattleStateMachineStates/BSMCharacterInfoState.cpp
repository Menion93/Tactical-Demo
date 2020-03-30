// Fill out your copyright notice in the Description page of Project Settings.

#include "BSMCharacterInfoState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"


UBSMCharacterInfoState::UBSMCharacterInfoState()
{

}

void UBSMCharacterInfoState::OnEnter()
{
	TArray<UAction*> ActionList = GetActionEntryList();
	BattleManager->GameMode->BattleUI->OpenActionMenu(ActionList);
}

bool UBSMCharacterInfoState::InputEventB()
{
	BattleManager->GameMode->BattleUI->CloseActionMenu();
	StateMachine->TransitionToState(StateMachine->PrevState);
	return true;
}

TArray<UAction*> UBSMCharacterInfoState::GetActionEntryList()
{
	TArray<TSubclassOf<class UAction>> ActionList = BattleManager->GameMode->BattleUI->ActionMenu->MenuActions;

	TArray<UAction*> ActionMenuEntries;

	for (auto& ActionMenuClass : ActionList)
	{
		//UAction* Action = NewObject<UAction>(
		//	this,
		//	ActionMenuClass,
		//	RF_NoFlags,
		//	ActionMenuClass.GetDefaultObject());

		UAction* Action = NewObject<UAction>(
			this,
			ActionMenuClass);

		Action->Init(BattleManager);

		if (Action->CanExecuteAction())
		{
			ActionMenuEntries.Add(Action);
		}
	}

	return ActionMenuEntries;
}

