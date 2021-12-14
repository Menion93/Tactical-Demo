// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleSystem/Actions/Action.h"
#include "Characters/GCharacter.h"
#include "BattleSystem/BattleManager.h"
#include "AITacticalDecisionMaking.generated.h"

/**
 * 
 */
class AAIFireTeam;

UCLASS(Blueprintable)
class TACTICALGAME_API UAITacticalDecisionMaking : public UObject
{
	GENERATED_BODY()

public:
	//UAITacticalDecisionMaking();

	UPROPERTY(BlueprintReadWrite)
	ABattleManager* BattleManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGCharacter* CurrentCharacter;


public:
	UFUNCTION()
	void Init(ABattleManager* MyBattleManager);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAction* GenerateNextAction(AAIFireTeam* FT);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	AGCharacter* GetNextAICharacter(AAIFireTeam* FT);


};
