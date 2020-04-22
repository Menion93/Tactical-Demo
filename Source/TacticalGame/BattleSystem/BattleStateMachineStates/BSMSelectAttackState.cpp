// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMSelectAttackState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"


UBSMSelectAttackState::UBSMSelectAttackState()
{

}

void UBSMSelectAttackState::OnEnter()
{
	BattleManager->GameMode->BattleUI->OpenAttackMenu(StateMachine->OffensiveOptions);

	FTile Tile = Grid->GetTile(StateMachine->TargetCharacter->CurrentTileIndex);
	BattleManager->GameMode->Camera->LerpToPosition(Tile.TileCenter);
}

bool UBSMSelectAttackState::InputEventB(float DeltaTime)
{
	BattleManager->GameMode->BattleUI->CloseAttackMenu();
	StateMachine->TransitionToPrevState();
	return true;
}
