// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMDeselectedState.h"
#include "Globals/TacticalGameGameMode.h"
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
	if (BattleManager->SelectedTile->Character)
	{
		// this will show an aura or spawn a decal under the character
		AControllableCharacter* Character = Cast<AControllableCharacter>(BattleManager->SelectedTile->Character);

		// if is a controllable character
		if (Character)
		{
			BattleManager->GameMode->BattleUI->SetCharacterBar(Character->State);
			Character->Selected();
			Character->ShowPerimeter(true);
			BattleManager->CurrentCharacter = Character;
			BattleManager->TransitionToState(CombatStateE::CHARACTER_SELECTED);
		}
		// Otherwise show character info
		else
		{
			BattleManager->NotAlliedCharacter = Cast<AGCharacter>(BattleManager->SelectedTile->Character);
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
			if (BattleManager->SelectedTile && BattleManager->SelectedTile->Direction2Neighbours.Contains(Index))
			{
				ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

				BattleManager->SelectedTile = BattleManager->SelectedTile->Direction2Neighbours[Index].Key;
				TileMap->SetCursorToTile(BattleManager->SelectedTile);
				GameMode->GameDirector->Camera->MoveToTile(BattleManager->SelectedTile);

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


void UBSMDeselectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}