// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/Actions/Action.h"
#include "ActionableAction.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UActionableAction : public UAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool MoveFirst;

	UPROPERTY(BlueprintReadWrite)
	bool mActionDone = false;

private:
	bool HasMoved;
	bool HasSimulated;

	UObject* Actionable;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MyInit(
		ABattleManager* BM,
		UObject* MyActionable,
		AGCharacter* MyCharacter,
		AGCharacter* MyTarget,
		FTileIndex MyTile);

	bool MoveTo();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTileIndex GetNearestTileInRange();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool ExecuteAction();

	virtual bool PlayAction_Implementation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ActionDone();

};
