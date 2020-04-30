// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMSelectEnemyState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"
#include "TopViewCamera.h"


UBSMSelectEnemyState::UBSMSelectEnemyState()
{

}

void UBSMSelectEnemyState::OnEnter()
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

	EnemyIndex = 0;
	FTile EnemyTile = Grid->GetTile(StateMachine->Targets[EnemyIndex]->CurrentTileIndex);
	BattleManager->GameMode->Camera->LerpToPosition(EnemyTile.TileCenter);
	StateMachine->TargetCharacter = StateMachine->Targets[EnemyIndex];
}


bool UBSMSelectEnemyState::InputEventLAxis(float DeltaTime)
{
	if (Input->LAxis_DOWN && Input->LHardAxis.X != 0)
	{
		EnemyIndex = int(EnemyIndex + Input->LHardAxis.X);
		EnemyIndex = EnemyIndex < 0 ? StateMachine->Targets.Num() - 1 : EnemyIndex;
		EnemyIndex = EnemyIndex == StateMachine->Targets.Num() ? 0 : EnemyIndex;

		FTile Tile = Grid->GetTile(StateMachine->Targets[EnemyIndex]->CurrentTileIndex);
		BattleManager->GameMode->Camera->LerpToPosition(Tile.TileCenter);

		StateMachine->TargetCharacter = StateMachine->Targets[EnemyIndex];
		return true;
	}

	return false;
}

bool UBSMSelectEnemyState::InputEventA(float DeltaTime)
{
	TArray<UObject*> OffensiveOptions = StateMachine->CurrentCharacter->GetOffensiveOptions();

	StateMachine->Actionables = OffensiveOptions
		.FilterByPredicate([this](auto& Object) {
			IActionable* OffensiveOption = Cast<IActionable>(Object);
			return OffensiveOption->Execute_IsInRange(Object, this->StateMachine->CurrentCharacter, this->StateMachine->TargetCharacter);
		}
	);

	StateMachine->TransitionToState(CombatStateE::SELECT_ATTACK);
	return true;
}


bool UBSMSelectEnemyState::InputEventB(float DeltaTime)
{
	StateMachine->TransitionToPrevState();
	StateMachine->TargetCharacter = PrevTargetChar;
	BattleManager->GameMode->Camera->LerpToPosition(BattleManager->GetSelectedTile().TileCenter);

	return true;
}
