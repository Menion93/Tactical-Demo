// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/CharacterState.h"
#include "BattleSystem/Actions/Action.h"
#include "AITacticalDecisionMaking.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UAITacticalDecisionMaking : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TArray<UCharacterState*> AICharacters;

};
