// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIBrain.h"
#include "Characters/GCharacter.h"
#include "TacticalAIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterHit, AGCharacter*, Target);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALGAME_API UTacticalAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTacticalAIComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAIBrain> MindClass;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	UAIBrain* Mind;

public:	

	UFUNCTION(BlueprintCallable)
	UAIBrain* GetMind();

	UFUNCTION(BlueprintCallable)
	UAction* GetAction();

	UFUNCTION()
	void SendHitMessage(AGCharacter* Target);

	UPROPERTY(BlueprintAssignable)
	FOnCharacterHit OnCharacterHit;

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
