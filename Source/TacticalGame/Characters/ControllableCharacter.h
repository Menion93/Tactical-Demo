// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCharacter.h"
#include "ControllableCharacter.generated.h"


class UCharacterState;
/**
 * 
 */
UCLASS()
class TACTICALGAME_API AControllableCharacter : public AGCharacter
{
	GENERATED_BODY()

public:

	AControllableCharacter();

	UPROPERTY(EditAnywhere)
	UCharacterState* State;

public:
	virtual void Tick(float DeltaTime) override;

	void Selected();
};