// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionableAction.h"
#include "Characters/GCharacter.h"
#include "Globals/TacticalGameMode.h"
#include "TopViewCamera.h"


void UActionableAction::Init(
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

	HasMoved = false;

	MoveFirst = !(Character->CurrentTileIndex == FromTileIndex);

	if (!MoveFirst && Character->CurrentTileIndex == FromTileIndex)
	{
		FTileIndex NearestTileIndex = GetNearestTileInRange();

		if (!(NearestTileIndex == FromTileIndex))
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
			ActionableObj->Execute_SimulateAction(Actionable, Character, Target);
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

