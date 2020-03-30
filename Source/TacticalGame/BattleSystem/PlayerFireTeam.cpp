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
	BagState = NewObject<UBSMBagState>(this, TEXT("BagState"));
	SelectEnemyState = NewObject<UBSMSelectEnemyState>(this, TEXT("SelectEnemyState"));
	SelectAttackState = NewObject<UBSMSelectAttackState>(this, TEXT("SelectAttackState"));

	DeselectedState->Init(this, MoveGridSpeed, DelayToSpeed);
	CharacterSelectedState->Init(this, MoveGridSpeed, DelayToSpeed);
	CharacterInfoState->Init(this);
	BagState->Init(this);
	SelectEnemyState->Init(this);
	SelectAttackState->Init(this);

	StateMachine.Emplace(CombatStateE::DESELECTED_STATE, DeselectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_SELECTED, CharacterSelectedState);
	StateMachine.Emplace(CombatStateE::CHARACTER_INFO, CharacterInfoState);
	StateMachine.Emplace(CombatStateE::OPEN_BAG, BagState);
	StateMachine.Emplace(CombatStateE::SELECT_ATTACK, SelectAttackState);
	StateMachine.Emplace(CombatStateE::SELECT_ENEMY, SelectEnemyState);
}

void APlayerFireTeam::PlayTurn_Implementation()
{
	if (!StateMachine[CurrentState]->IsInputDisabled())
	{
		StateMachine[CurrentState]->PlayState();
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

	if (CurrentCharacter)
	{
		if (CurrentCharacter->State->CurrentActionPoints > 0)
		{
			CurrentState = CombatStateE::CHARACTER_SELECTED;
		}
		else
		{
			CurrentState = CombatStateE::DESELECTED_STATE;
		}
	}
}

void APlayerFireTeam::OnTurnStart_Implementation()
{
	Super::OnTurnStart_Implementation();

	SelectedTile = Characters[0]->CurrentTileIndex;
	BattleManager->GameMode->Grid->SetCursorToTile(SelectedTile);
	BattleManager->GameMode->Camera->LookAtPosition(BattleManager->GetSelectedTile().TileCenter);

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

bool APlayerFireTeam::IsWinConditionSatisfied_Implementation()
{
	return false;
}

bool APlayerFireTeam::IsTurnEnded_Implementation()
{
	return false;
}

void APlayerFireTeam::TransitionToState(CombatStateE State)
{
	PrevState = CurrentState;
	CurrentState = State;
	StateMachine[CurrentState]->OnEnter();
}

void APlayerFireTeam::SpawnTeam()
{
	for (auto& Character : Characters)
	{
		BattleManager->Grid->SnapToGrid(Character);

		UCharacterState* CharacterState = NewObject<UCharacterState>(
			this, Character->StateClass->GetFName(), RF_NoFlags, Character->StateClass.GetDefaultObject());

		Character->Init();
		Character->State = CharacterState;

		Character->ComputeShortestPaths();
		Character->ComputePerimeterPoints();
	}

	int PointIndex = 0;
	TArray<UCharacterState*> Team = BattleManager->GameMode->Party->GetTeam();

	for (auto& SpawnPoint : SpawnPoints)
	{
		UWorld* World = GetWorld();

		if (World)
		{

			AGCharacter* Character = World->SpawnActor<AGCharacter>(
				Team[PointIndex]->ActorCharacterClass,
				SpawnPoint->GetActorLocation(),
				FRotator::ZeroRotator);

			Character->Init();
			Team[PointIndex]->ActorCharacter = Character;
			Character->State = Team[PointIndex];

			FTile* Tile = BattleManager->Grid->SnapToGrid(Character);

			Characters.Add(Character);

			Character->ComputeShortestPaths();
			Character->ComputePerimeterPoints();
		}
	}
}