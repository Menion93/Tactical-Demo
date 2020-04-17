// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSMState.h"
#include "BSMSelectEnemyState.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBSMSelectEnemyState : public UBSMState
{
	GENERATED_BODY()

public:
	UBSMSelectEnemyState();

	int EnemyIndex;

private:
	AGCharacter* PrevTargetChar;

public:

	bool InputEventA(float DeltaTime) override;
	bool InputEventB(float DeltaTime) override;

	bool InputEventLAxis(float DeltaTime) override;

	void OnEnter() override;


};
