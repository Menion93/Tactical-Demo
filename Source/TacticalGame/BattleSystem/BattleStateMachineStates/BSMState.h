// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Engine/World.h"
#include "Grid/Grid.h"
#include "Globals/GPlayerController.h"
#include "BSMState.generated.h"


class ABattleManager;
class APlayerFireTeam;

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMState : public UObject
{
	GENERATED_BODY()
	
public:
	UBSMState();

protected:
	ABattleManager* BattleManager;
	AGPlayerController* Input;
	AGrid* Grid;
	APlayerFireTeam* StateMachine;

	bool InputDisabled = false;

public:
	virtual void Init(APlayerFireTeam* SM);

	bool IsInputDisabled();
	void DisableInput(bool DisInput);
	virtual void PlayState();

	void BindState();
	void UnbindState();

	virtual bool InputEventX();
	virtual bool InputEventY();
	virtual bool InputEventA();
	virtual bool InputEventB();

	virtual bool InputEventStart();
	virtual bool InputEventPause();

	virtual bool InputEventR1();
	virtual bool InputEventR2();

	virtual bool InputEventL1();
	virtual bool InputEventL2();

	virtual bool InputEventLAxis();
	virtual bool InputEventRAxis();

	virtual bool InputEventPadUpDown();
	virtual bool InputEventPadLeftRight();

	virtual void OnEnter();





};
