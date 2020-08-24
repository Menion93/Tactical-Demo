// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionableAction.h"
#include "Characters/GCharacter.h"
#include "Globals/TacticalGameMode.h"
#include "TopViewCamera.h"


void UActionableAction::MyInit_Implementation(
	ABattleManager* MyBM,
	UObject* MyActionable,
	AGCharacter* MyCharacter,
	AGCharacter* MyTarget,
	FTileIndex MyTile)
{
	BattleManager = MyBM;
	Character = MyCharacter;
	Target = MyTarget;
	FromTileIndex = MyTile;
	Actionable = MyActionable;
	Input = Cast<AGPlayerController>(MyCharacter->GetWorld()->GetFirstPlayerController());

	HasMoved = false;

	AGCharacter* CharInSelectedTile = Character->Grid->GetTile(FromTileIndex).Character;

	MoveFirst = !(Character->CurrentTileIndex == FromTileIndex) && MyTarget != CharInSelectedTile;

	if (!MoveFirst)
	{
		FTileIndex NearestTileIndex = GetNearestTileInRange();

		if (!(NearestTileIndex == FromTileIndex) && !(NearestTileIndex == Character->CurrentTileIndex))
		{
			FromTileIndex = NearestTileIndex;
			MoveFirst = true;
		}
	}

};

bool UActionableAction::PlayAction_Implementation(float DeltaTime)
{
	if (!HasMoved && MoveFirst)
	{
		HasMoved = MoveTo();
	}
	else
	{
		HasMoved = true;
	}
	
	if(HasMoved)
	{
		if (!HasSimulated)
		{
			IActionable* ActionableObj = Cast<IActionable>(Actionable);

			if (ActionableObj)
			{
				ActionableObj->Execute_SimulateAction(Actionable, Character, Target);
			}
			HasSimulated = true;
		}
		return ExecuteAction();
	}

	return false;
}


bool UActionableAction::MoveTo()
{
	if (Character->PathfindingComponent->MoveTo(FromTileIndex))
	{
		Character->Grid->TransferCharacterToTile(Character->CurrentTileIndex, FromTileIndex);
		Character->CurrentTileIndex = FromTileIndex;
		Character->FireTeam->RecomputeAllCharactersMetadata();
		return true;
	}
	else
	{
		FVector ActorLoc = Character->GetActorLocation();
		BattleManager->GameMode->Camera->LerpToPosition(
			FVector(ActorLoc.X, ActorLoc.Y, ActorLoc.Z - Character->GetDefaultHalfHeight()));
		return false;
	}

	return false;
}


void UActionableAction::ActionDone()
{
	mActionDone = true;
}
