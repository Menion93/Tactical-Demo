// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableCharacter.h"
#include "Engine/World.h"

AControllableCharacter::AControllableCharacter()
{
}

void AControllableCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		FVector Direction = FVector(Input->Axis.X, Input->Axis.Y, GetActorLocation().Z);
		AddMovementInput(Direction, Speed);

		if (Input->Axis.X != 0 || Input->Axis.Y != 0)
		{
			SetActorRotation(FVector(Direction.X, Direction.Y, 0).ToOrientationRotator());
		}
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