// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/BattleStateMachineStates/BSMSelectEnemyState.h"
#include "BSMSelectEnemyFromTileState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMSelectEnemyFromTileState : public UBSMSelectEnemyState
{
	GENERATED_BODY()

public:

	bool InputEventA(float DeltaTime) override;

};
