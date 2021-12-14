// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/FireTeam.h"
#include "AI/AITacticalDecisionMaking.h"
#include "AIFireTeam.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API AAIFireTeam : public AFireTeam
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UAction* CurrentAction;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAITacticalDecisionMaking> TacticalAIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAITacticalDecisionMaking* TacticalAI;

public:

	void PlayTurn_Implementation(float DeltaTime) override;

	void Init_Implementation(ABattleManager* BM) override;
	void OnTurnStart_Implementation() override;

};
