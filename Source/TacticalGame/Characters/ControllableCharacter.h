// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCharacter.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option")
	float Speed = 100;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void Selected();
	void HandleInput();
};
