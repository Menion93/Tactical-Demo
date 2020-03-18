// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableCharacter.h"
#include "Engine/World.h"

AControllableCharacter::AControllableCharacter()
{
}

void AControllableCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();

	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());
}


// Called every frame
void AControllableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AControllableCharacter::Selected()
{

}

void AControllableCharacter::HandleInput()
{
	if (!Input->Axis.IsZero())
	{
		this->AddMovementInput(FVector(Input->Axis.X, Input->Axis.Y, this->GetActorLocation().Z), Speed);
	}
}

TArray<UAction*> AControllableCharacter::GetAdditionalActions()
{
	TArray<UAction*> AdditionalActions;
	return AdditionalActions;
}

void AControllableCharacter::ReverseAction()
{
	if (ActionsBuffer.Num() > 0)
	{
		int Index = ActionsBuffer.Num() - 1;
		ActionsBuffer[Index]->ReverseAction();
		ActionsBuffer.RemoveAt(Index);
	}
}