// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UInputController : public UObject
{
	GENERATED_BODY()

public:
	UInputController();

public:
	virtual void DisableInputController();
	virtual void EnableInputController();
	
};
