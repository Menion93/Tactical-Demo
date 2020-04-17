// Fill out your copyright notice in the Description page of Project Settings.

#include "BSMCharacterInfoState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"


UBSMCharacterInfoState::UBSMCharacterInfoState()
{

}

void UBSMCharacterInfoState::OnEnter()
{
	Target = StateMachine->TargetCharacter;
	Tile = BattleManager->GetSelectedTile();
	TArray<UAction*> ActionList = GetActionEntryList();
	BattleManager->GameMode->BattleUI->OpenActionMenu(ActionList);
}

bool UBSMCharacterInfoState::InputEventB(float DeltaTime)
{
	BattleManager->GameMode->BattleUI->CloseActionMenu();
	StateMachine->TargetCharacter = nullptr;
	StateMachine->TransitionToPrevState();
	return true;
}

void UBSMCharacterInfoState::OnRestore()
{
	StateMachine->TargetCharacter = Target;
	BattleManager->GameMode->Camera->LerpToPosition(Tile.TileCenter);
	TArray<UAction*> ActionList = GetActionEntryList();
	BattleManager->GameMode->BattleUI->OpenActionMenu(ActionList);
}

TArray<UAction*> UBSMCharacterInfoState::GetActionEntryList()
{
	TArray<TSubclassOf<class UAction>> ActionList = BattleManager->GameMode->BattleUI->ActionMenu->MenuActions;

	TArray<UAction*> ActionMenuEntries;

	for (auto& ActionMenuClass : ActionList)
	{

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

