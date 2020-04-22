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
	TArray<UBattleMenuItem*> MenuItemList = GetMenuItemsEntryList();
	BattleManager->GameMode->BattleUI->OpenActionMenu(MenuItemList);
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
	TArray<UBattleMenuItem*> MenuItemList = GetMenuItemsEntryList();
	BattleManager->GameMode->BattleUI->OpenActionMenu(MenuItemList);
}

TArray<UBattleMenuItem*> UBSMCharacterInfoState::GetMenuItemsEntryList()
{
	TArray<TSubclassOf<class UBattleMenuItem>> MenuItemList = BattleManager->GameMode->BattleUI->ActionMenu->MenuItemList;

	TArray<UBattleMenuItem*> MenuItemsEntries;

	for (auto& MenuItemClass : MenuItemList)
	{

		UBattleMenuItem* MenuItem = NewObject<UBattleMenuItem>(
			this,
			MenuItemClass);

		MenuItem->Init(BattleManager);

		if (MenuItem->ShowMenuOption())
		{
			MenuItemsEntries.Add(MenuItem);
		}
	}

	return MenuItemsEntries;
}

