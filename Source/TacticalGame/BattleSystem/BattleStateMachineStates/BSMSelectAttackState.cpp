// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMSelectAttackState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"


UBSMSelectAttackState::UBSMSelectAttackState()
{

}

void UBSMSelectAttackState::OnEnter()
{
	BattleManager->GameMode->BattleUI->OpenAttackMenu(StateMachine->Actionables);

	FTile Tile = Grid->GetTile(StateMachine->TargetCharacter->CurrentTileIndex);
	BattleManager->GameMode->Camera->LerpToPosition(Tile.TileCenter);
	BattleManager->GameMode->BattleUI->SetCharacterBar2(StateMachine->TargetCharacter->State);
}

bool UBSMSelectAttackState::InputEventB(float DeltaTime)
{
	BattleManager->GameMode->BattleUI->CloseAttackMenu();
	BattleManager->GameMode->BattleUI->HideCharacterBar2();
	StateMachine->TransitionToPrevState();
	return true;
}
