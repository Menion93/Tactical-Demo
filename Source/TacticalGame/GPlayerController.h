// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputController.h"
#include "GPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API AGPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	AGPlayerController();

	UInputController* CurrentInputController;

	TMap<FName, UInputController*> tag2input;


public:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void BindControllerInput(FName MODE);
	void AddInputController(FName key, UInputController* IC);
	
};
