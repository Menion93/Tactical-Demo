// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"
#include "BattleManager.h"

APlayerFireTeam::APlayerFireTeam()
{

}

void APlayerFireTeam::Init_Implementation(ABattleManager* BM)
{
	Super::Init_Implementation(BM);
	CurrentState = CombatStateE::DESELECTED_STATE;

	DeselectedState = NewObject<UBSMDeselectedState>(this, TEXT("DeselectedState"));
	CharacterSelectedState = NewObject<UBSMCharacterSelectedState>(this, TEXT("CharacterSelectedState"));
	CharacterInfoState = NewObject<UBSMCharacterInfoState>(this, TEXT("CharacterInfoState"));
	SelectEnemyState = NewObject<UBSMSelectEnemyState>(this, TEXT("SelectEnemyState"));
	SelectEnemyFromTileState = NewObject<UBSMSelectEnemyFromTileState>(this, TEXT("SelectEnemyFromTileState"));
	SelectAttackState = NewObject<UBSMSelectAttackState>(this, TEXT("SelectAttackState"));
	SelectSupportActionState = NewObject<UBSMSelectSupportActionState>(this, TEXT("SelectSupportAction"));
	SelectAllyState = NewObject<UBSMSelectAllyState>(this, TEXT("SelectAllyState"));
	SelectAllyFromTileState = NewObject<UBSMSelectAllyFromTileState>(this, TEXT("SelectAllyFromTileState"));
	UnitInfoState = NewObject<UBSMUnitInfoState>(this, TEXT("UnitInfoState"));

	DeselectedState->InitState(this, MoveGridSpeed, DelayToSpeed);
	CharacterSelectedState->InitState(this, MoveGridSpeed, DelayToSpeed);
	CharacterInfoState->Init(this);
	SelectEnemyState->Init(this);
	SelectEnemyFromTileState->Init(this);
	SelectAttackState->Init(this);
	SelectSupportActionState->Init(this);
	SelectAllyState->Init(this);
	SelectAllyFromTileState->Init(this);
	UnitInfoState->Init(this);

	StateMachine.Emplace(CombatStateE::DESELECTED_STATE, DeselectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_SELECTED, CharacterSelectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_INFO, CharacterInfoState);
	StateMachine.Emplace(CombatStateE::SELECT_ATTACK, SelectAttackState);
	StateMachine.Emplace(CombatStateE::SELECT_ENEMY, SelectEnemyState);
	StateMachine.Emplace(CombatStateE::SELECT_ENEMY_FROM_TILE, SelectEnemyFromTileState);
	StateMachine.Emplace(CombatStateE::SELECT_SUPPORT_ACTION, SelectSupportActionState);
	StateMachine.Emplace(CombatStateE::SELECT_ALLY, SelectAllyState);
	StateMachine.Emplace(CombatStateE::SELECT_ALLY_FROM_TILE, SelectAllyFromTileState);
	StateMachine.Emplace(CombatStateE::UNIT_INFO, UnitInfoState);
}

void APlayerFireTeam::PlayTurn_Implementation(float DeltaTime)
{
	if (!StateMachine[CurrentState]->IsInputDisabled())
	{
		StateMachine[CurrentState]->PlayState(DeltaTime);
	}
}

void APlayerFireTeam::OnActionEnd_Implementation()
{
	if (BattleManager->CurrentAction->ReversibleAction)
	{
		CurrentCharacter->ActionsBuffer.Add(BattleManager->CurrentAction);
	}
	else
	{
		CurrentCharacter->ActionsBuffer.Empty();
	}

	if (CurrentCharacter && CurrentCharacter->State->CurrentActionPoints < 0)
	{
		CurrentState = CombatStateE::DESELECTED_STATE;
	}
}

void APlayerFireTeam::OnTurnStart_Implementation()
{
	Super::OnTurnStart_Implementation();

	SelectedTile = Characters[0]->CurrentTileIndex;
	BattleManager->GameMode->Grid->SetCursorToTile(SelectedTile);
	BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);
	BattleManager->GameMode->Grid->ShowCursor(true);

	CurrentState = CombatStateE::DESELECTED_STATE;

	for (auto Char : Characters)
	{
		if (Char->State->CurrentHealth > 0)
		{
			// reset action points
			Char->State->ResetActionPoints();
		}
	}
}

void APlayerFireTeam::OnTurnEnd_Implementation()
{
	BattleManager->GameMode->Grid->ShowCursor(false);
	for (auto& Character : Characters)
	{
		Character->PerimeterComponent->ShowPerimeter(false);
	}
}

bool APlayerFireTeam::IsWinConditionSatisfied_Implementation()
{
	return false;
}


void APlayerFireTeam::EndCharacterTurn()
{
	StatesHistory.Empty();
	TransitionToState(CombatStateE::DESELECTED_STATE);
	CurrentCharacter->PerimeterComponent->ShowPerimeter(false);
	CurrentCharacter->PathfindingComponent->ShowShortestPath(false);
}


void APlayerFireTeam::TransitionToState(CombatStateE State)
{
	StatesHistory.Add(CurrentState);
	CurrentState = State;
	StateMachine[CurrentState]->OnEnter();
}

void APlayerFireTeam::TransitionToPrevState()
{
	if (StatesHistory.Num() < 1)
	{
		return;
	}

	CurrentState = StatesHistory.Pop();
	StateMachine[CurrentState]->OnRestore();
}

void APlayerFireTeam::SpawnTeam()
{
	for (auto& Character : Characters)
	{
		BattleManager->Grid->SnapToGrid(Character);

		UCharacterState* CharacterState = NewObject<UCharacterState>(
			Character, Character->StateClass->GetFName(), RF_NoFlags, Character->StateClass.GetDefaultObject());

		CharacterState->ActorCharacter = Character;
		CharacterState->LoadState();

		Character->Init(this, CharacterState);
	}

}