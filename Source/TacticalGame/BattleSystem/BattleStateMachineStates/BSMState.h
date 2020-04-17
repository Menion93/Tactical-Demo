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

	virtual void PlayState(float DeltaTime);

	virtual bool InputEventX(float DeltaTime);
	virtual bool InputEventY(float DeltaTime);
	virtual bool InputEventA(float DeltaTime);
	virtual bool InputEventB(float DeltaTime);

	virtual bool InputEventStart(float DeltaTime);
	virtual bool InputEventPause(float DeltaTime);

	virtual bool InputEventR1(float DeltaTime);
	virtual bool InputEventR2(float DeltaTime);

	virtual bool InputEventL1(float DeltaTime);
	virtual bool InputEventL2(float DeltaTime);

	virtual bool InputEventLAxis(float DeltaTime);
	virtual bool InputEventRAxis(float DeltaTime);

	virtual bool InputEventPadUpDown(float DeltaTime);
	virtual bool InputEventPadLeftRight(float DeltaTime);

	virtual void OnEnter();
	virtual void OnRestore();

};
