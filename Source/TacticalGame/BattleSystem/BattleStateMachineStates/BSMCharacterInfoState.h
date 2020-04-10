// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BattleSystem/Actions/Action.h"
#include "BSMCharacterInfoState.generated.h"


/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMCharacterInfoState : public UBSMState
{
	GENERATED_BODY()
	
public:
	UBSMCharacterInfoState();

public:
	bool InputEventB(float DeltaTime) override;
	void OnEnter() override;
	TArray<UAction*> GetActionEntryList();

};
