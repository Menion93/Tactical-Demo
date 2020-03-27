// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMDeselectedState.h"
#include "Globals/TacticalGameMode.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Engine/World.h"


UBSMDeselectedState::UBSMDeselectedState()
{

}

void UBSMDeselectedState::InputEventX()
{

}

void UBSMDeselectedState::InputEventY()
{

}

// When selecting a Tile
void UBSMDeselectedState::InputEventA()
{
	AGCharacter* Character = BattleManager->GetCurrentTile().Character;

	if (Character)
	{
		// if is a controllable character
		if (BattleManager->GetPlayerFireTeam()->InFireTeam(Character))
		{
			if (Character->State->CurrentActionPoints < 1)
			{
				return;
			}

			BattleManager->GameMode->BattleUI->SetCharacterBar(Character->State);
			Character->Selected();
			Character->ShowPerimeter(true);
			BattleManager->CurrentCharacter = Character;
			StateMachine->TransitionToState(CombatStateE::CHARACTER_SELECTED);
		}
		// Otherwise show character info
		else
		{
			BattleManager->NotAlliedCharacter = Character;
			StateMachine->TransitionToState(CombatStateE::CHARACTER_INFO);
		}
	}
}

void UBSMDeselectedState::InputEventB()
{

}


void UBSMDeselectedState::InputEventLAxis()
{
	if (!Input->HardAxis.IsZero()) {

		if (!CooldownMovementGrid || Input->Axis_DOWN)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				World->GetTimerManager().ClearTimer(timerHandle);
			}

			if (AxisReleased)
			{
				time = 0.25;
			}

			AxisReleased = false;

			FTileIndex Index(Input->HardAxis);
			FTile CurrentTile = BattleManager->GetCurrentTile();

			if (CurrentTile.Direction2Neighbours.Contains(Index))
			{
				ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());

				BattleManager->SelectedTile = CurrentTile.Direction2Neighbours[Index].Key->Index;
				Grid->SetCursorToTile(BattleManager->SelectedTile);
				GameMode->Camera->LookAtPosition(BattleManager->GetCurrentTile().TileCenter);

				if (World)
				{
					World->GetTimerManager().SetTimer(timerHandle, this, &UBSMDeselectedState::ResetCooldownMovementGrid, time);
				}

				CooldownMovementGrid = true;
			}
		}
	}	
	else
	{
		AxisReleased = true;
	}
}

void UBSMDeselectedState::InputEventR1()
{

}

void UBSMDeselectedState::InputEventL1()
{

}

void UBSMDeselectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}