// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputController.h"
#include "WorldInputController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UWorldInputController : public UInputController
{
	GENERATED_BODY()

public:
	UWorldInputController();

public:
	virtual void DisableInputController() override;
	virtual void EnableInputController() override;

	
};
