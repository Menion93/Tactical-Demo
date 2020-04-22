// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMSelectSupportActionState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"


UBSMSelectSupportActionState::UBSMSelectSupportActionState()
{

}

void UBSMSelectSupportActionState::OnEnter()
{
	BattleManager->GameMode->BattleUI->OpenSupportOptionMenu(StateMachine->SupportOptions);

	FTile Tile = Grid->GetTile(StateMachine->TargetCharacter->CurrentTileIndex);
	BattleManager->GameMode->Camera->LerpToPosition(Tile.TileCenter);
}

bool UBSMSelectSupportActionState::InputEventB(float DeltaTime)
{
	BattleManager->GameMode->BattleUI->CloseSupportOptionMenu();
	StateMachine->TransitionToPrevState();
	return true;
}
