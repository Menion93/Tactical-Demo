// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleSystem/Actions/Action.h"
#include "ActionMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UActionMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UAction>> MenuActions;
	

};