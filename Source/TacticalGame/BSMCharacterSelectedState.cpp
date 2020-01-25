// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"
#include "TacticalGameGameMode.h"
#include "Engine/World.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState(){}

UAction* UBSMCharacterSelectedState::PlayState()
{
	UAction* action = NewObject<UAction>(this, TEXT("Action"));

	// Deselect the character
	if (Input->B)
	{
		BattleManager->CurrentCharacter = nullptr;
		BattleManager->CurrentState = CombatStateE::DESELECTED_STATE;
	}

	// Move the cursor
	if (!Input->HardAxis.IsZero())
	{
		if (!CooldownMovementGrid || Input->Axis_DOWN)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				World->GetTimerManager().ClearTimer(timerHandle);
			}

			if (AxisReleased)
			{
				time = 0.5;
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
					World->GetTimerManager().SetTimer(timerHandle, this, &UBSMCharacterSelectedState::ResetCooldownMovementGrid, time);
				}

				CooldownMovementGrid = true;
			}
		}
	}
	else
	{
		AxisReleased = true;
	}

	return nullptr;

}

void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}