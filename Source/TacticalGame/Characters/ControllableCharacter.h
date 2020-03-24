// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCharacter.h"
#include "BattleSystem/Actions/Action.h"
#include "Globals/GPlayerController.h"
#include "ControllableCharacter.generated.h"


/**
 * 
 */
UCLASS()
class TACTICALGAME_API AControllableCharacter : public AGCharacter
{
	GENERATED_BODY()

public:

	AControllableCharacter();

	AGPlayerController* Input;

	// List of reversible actions done in the current turn
	TArray<UAction*> ActionsBuffer;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void Selected();
	void HandleInput();

	TArray<UAction*> GetAdditionalActions();

	void ReverseAction();
};
