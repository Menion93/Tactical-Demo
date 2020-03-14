// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid/FTile.h"
#include "Engine/World.h"
#include "Grid/ATileMapSet.h"
#include "Globals/GPlayerController.h"
#include "BSMState.generated.h"


class UBattleManager;

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
	UBattleManager* BattleManager;
	AGPlayerController* Input;
	AATileMapSet* TileMap;

	bool InputDisabled = false;

public:
	virtual void Init();
	bool IsInputDisabled();
	void DisableInput(bool DisInput);
	virtual void PlayState();

	void BindState();
	void UnbindState();

	virtual void InputEventX();
	virtual void InputEventY();
	virtual void InputEventA();
	virtual void InputEventB();

	virtual void InputEventStart();
	virtual void InputEventPause();

	virtual void InputEventR1();
	virtual void InputEventR2();

	virtual void InputEventL1();
	virtual void InputEventL2();

	virtual void InputEventLAxis();
	virtual void InputEventRAxis();

	virtual void InputEventPadUpDown();
	virtual void InputEventPadLeftRight();





};
