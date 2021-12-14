// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/BattleStateMachineStates/BSMState.h"
#include "BattleSystem/Actions/Action.h"
#include "UI/BattleMenuItem.h"
#include "BSMUnitInfoState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMUnitInfoState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMUnitInfoState();

private:
	AGCharacter* Target;
	FTile Tile;

public:
	bool InputEventB(float DeltaTime) override;

	void OnEnter() override;

	
};
