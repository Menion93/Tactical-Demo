// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputController.h"
#include "CombatInputController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UCombatInputController : public UInputController
{
	GENERATED_BODY()

public:
	UCombatInputController();

public:
	void DisableInputController() override;
	void EnableInputController() override;
	
};
