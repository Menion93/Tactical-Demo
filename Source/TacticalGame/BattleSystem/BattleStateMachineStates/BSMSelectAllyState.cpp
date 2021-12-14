// Fill out your copyright notice in the Description page of Project Settings.

#include "BSMSelectAllyState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/Actions/Actionable.h"
#include "TopViewCamera.h"

UBSMSelectAllyState::UBSMSelectAllyState()
{

}

void UBSMSelectAllyState::OnEnter()
{

	FTile Tile = Grid->GetTile(StateMachine->CurrentCharacter->CurrentTileIndex);
	FVector CharPosition = Tile.TileCenter;

	PrevTargetChar = StateMachine->TargetCharacter;

	AGrid* MyGrid = Grid;
	StateMachine->Targets.Sort([CharPosition, MyGrid](auto& A, auto& B)
	{
		return FVector::Distance(CharPosition, MyGrid->GetTile(A.CurrentTileIndex).TileCenter) <
			FVector::Distance(CharPosition, MyGrid->GetTile(B.CurrentTileIndex).TileCenter);
	});

	AllyIndex = 0;
	FTile AllyTile = Grid->GetTile(StateMachine->Targets[AllyIndex]->CurrentTileIndex);
	BattleManager->GameMode->Camera->LerpToPosition(AllyTile.TileCenter);
	StateMachine->TargetCharacter = StateMachine->Targets[AllyIndex];
	BattleManager->GameMode->BattleUI->SetCharacterBar2(StateMachine->TargetCharacter->State);

}


bool UBSMSelectAllyState::InputEventLAxis(float DeltaTime)
{
	if (Input->LAxis_DOWN && Input->LHardAxis.X != 0)
	{
		AllyIndex = int(AllyIndex + Input->LHardAxis.X);
		AllyIndex = AllyIndex < 0 ? StateMachine->Targets.Num() - 1 : AllyIndex;
		AllyIndex = AllyIndex == StateMachine->Targets.Num() ? 0 : AllyIndex;

		FTile Tile = Grid->GetTile(StateMachine->Targets[AllyIndex]->CurrentTileIndex);
		BattleManager->GameMode->Camera->LerpToPosition(Tile.TileCenter);

		StateMachine->TargetCharacter = StateMachine->Targets[AllyIndex];
		BattleManager->GameMode->BattleUI->SetCharacterBar2(StateMachine->TargetCharacter->State);

		return true;
	}

	return false;
}

bool UBSMSelectAllyState::InputEventA(float DeltaTime)
{
	TArray<UObject*> SupportOptions = StateMachine->CurrentCharacter->GetSupportOptions();

	StateMachine->Actionables = SupportOptions
		.FilterByPredicate([this](auto& Object) {
		IActionable* SupportOption = Cast<IActionable>(Object);
		FTileIndex TileIndex;
		return SupportOption->Execute_IsInRange(Object, TileIndex, this->StateMachine->CurrentCharacter, this->StateMachine->TargetCharacter);
	}
	);

	StateMachine->TransitionToState(CombatStateE::SELECT_SUPPORT_ACTION);
	return true;
}


bool UBSMSelectAllyState::InputEventB(float DeltaTime)
{
	StateMachine->TransitionToPrevState();
	StateMachine->TargetCharacter = PrevTargetChar;
	BattleManager->GameMode->Camera->LerpToPosition(BattleManager->GetSelectedTile().TileCenter);
	BattleManager->GameMode->BattleUI->HideCharacterBar2();
	return true;
}
