// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Globals/GPlayerController.h"
#include "BaseListView.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UBaseListView : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	AGPlayerController* Input;

	UPROPERTY(BlueprintReadWrite)
	UListView* ListView;

	UPROPERTY(BlueprintReadWrite)
	int Index;

public:


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void Init(TArray<UObject*> Entries, UListView* LV);

	UFUNCTION(BlueprintNativeEvent)
	void AxisInput();

	UFUNCTION(BlueprintNativeEvent)
	void AInput();

};
