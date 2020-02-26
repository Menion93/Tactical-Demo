// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMCharacterSelectedState.h"
#include "Globals/TacticalGameGameMode.h"
#include "Engine/World.h"

UBSMCharacterSelectedState::UBSMCharacterSelectedState(){}

void UBSMCharacterSelectedState::PlayState()
{
	// Deselect the character
	if (Input->B)
	{
		Input->B_DOWN = false;
		BattleManager->CurrentCharacter->ShowPerimeter(false);
		BattleManager->CurrentCharacter->ShowShortestPath(false);
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
				BattleManager->CurrentCharacter->DrawShortestPath(BattleManager->SelectedTile);
				BattleManager->CurrentCharacter->ShowShortestPath(true);
				UE_LOG(LogTemp, Warning, TEXT("hello3"))

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

}

void UBSMCharacterSelectedState::ResetCooldownMovementGrid()
{
	CooldownMovementGrid = false;
	time = 0.1;
}