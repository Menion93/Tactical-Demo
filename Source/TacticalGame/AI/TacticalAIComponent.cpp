// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TacticalAIComponent.h"
#include "BattleSystem/BattleManager.h"
#include "Globals/TacticalGameMode.h"
#include "Characters/CharacterState.h"

// Sets default values for this component's properties
UTacticalAIComponent::UTacticalAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTacticalAIComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	AGCharacter* OwnerChar = nullptr;

	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());

	check(GameMode != nullptr);

	if (Owner)
	{
		OwnerChar = Cast<AGCharacter>(Owner);
	}

	if (OwnerChar && MindClass)
	{
		Mind = NewObject<UAIBrain>(this, MindClass, OwnerChar->GetFName(), RF_NoFlags, MindClass.GetDefaultObject(), true);
		//Mind = NewObject<UAIBrain>(this, NAME_None, MindClass);

		Mind->Init(OwnerChar, GameMode);
	}
}

UAIBrain* UTacticalAIComponent::GetMind()
{
	return Mind;
}

UAction* UTacticalAIComponent::GetAction()
{
	return Mind->GetAction();
}

void UTacticalAIComponent::SendHitMessage(AGCharacter* Target)
{
	OnCharacterHit.Broadcast(Target);
}




// Called every frame
//void UTacticalAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

