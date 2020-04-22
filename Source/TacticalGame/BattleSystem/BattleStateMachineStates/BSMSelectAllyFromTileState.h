// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/BattleStateMachineStates/BSMState.h"
#include "BattleSystem/BattleStateMachineStates/BSMSelectAllyState.h"
#include "BSMSelectAllyFromTileState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMSelectAllyFromTileState : public UBSMSelectAllyState
{
	GENERATED_BODY()

public:
	bool InputEventA(float DeltaTime) override;

};
