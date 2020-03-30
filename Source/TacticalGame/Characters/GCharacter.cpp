// Fill out your copyright notice in the Description page of Project Settings.


#include "GCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Globals/TacticalGameMode.h"
#include "Grid/Grid.h"
#include "GameFramework/SpringArmComponent.h"
#include "Utils/Structs.h"


// Sets default values
AGCharacter::AGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

// Called when the game starts or when spawned
void AGCharacter::BeginPlay()
{
	Super::BeginPlay();	
	SpawnDefaultController();
}

void AGCharacter::Init()
{
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	Grid = GameMode->Grid;
	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());
}


// Called every frame
void AGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AGCharacter::IsInMeleeRange(AGCharacter* Enemy)
{
	return false;
}

bool AGCharacter::IsInLineOfSight(AGCharacter* Enemy)
{
	return false;
}

void AGCharacter::Shoot(AGCharacter* Enemy)
{

}

void AGCharacter::Melee(AGCharacter* Enemy)
{

}

void AGCharacter::GetDamage(float Damage)
{

}

TArray<UAction*> AGCharacter::GetAdditionalActions()
{
	TArray<UAction*> AdditionalActions;
	return AdditionalActions;
}

bool AGCharacter::MoveTo(FTileIndex TileIndex)
{
	bool IsMoving = PathIndex != -1;

	if (!IsMoving)
	{
		MovePoints = TArray<FVector>();
		UGridUtils::UnravelPath(Grid, ShortestPaths, TileIndex, MovePoints);
		PathIndex = 1;
	}

	FVector FlatLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - GetDefaultHalfHeight());
	float DistanceFromCheckpoint = FVector::Distance(FlatLocation, MovePoints[PathIndex]);
	if (DistanceFromCheckpoint < ToleranceBetweetCkpts)
	{
		if (PathIndex == MovePoints.Num() - 1)
		{
			PathIndex = -1;
			return true;
		}

		PathIndex = (PathIndex + 1) % MovePoints.Num();
	}
	
	FVector Direction = MovePoints[PathIndex] - FlatLocation;
	Direction.Normalize();

	AddMovementInput(Direction, Speed);
	SetActorRotation(FVector(Direction.X, Direction.Y, 0).ToOrientationRotator());

	return false;
}

void AGCharacter::ComputeShortestPaths()
{
	ShortestPaths = TMap<FTileIndex, FDijkstraNode>();
	UGridUtils::GetShortestPaths(Grid, ShortestPaths, CurrentTileIndex, 9999);
}


void AGCharacter::ComputePerimeterPoints()
{
	for (auto& Perimeter : Perimeters)
	{
		Perimeter->Destroy();
	}

	Perimeters = TArray<APerimeter*>();

	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());

	TArray<FVectorArray> PerimeterBlocks = UGridUtils::GetPerimeterPoints(
		Grid,
		ShortestPaths,
		State->MovementSpeed,
		GameMode->Grid->CellSize,
		GameMode->Grid->PerimeterVOffset);

	for (auto& perimeter : PerimeterBlocks)
	{
		APerimeter* Perimeter = GetWorld()->SpawnActor<APerimeter>(
			PerimeterClass, GetActorLocation(), FRotator::ZeroRotator);

		Perimeter->DrawPerimeter(perimeter.Array);
		Perimeter->SetActorHiddenInGame(true);
		Perimeters.Add(Perimeter);
	}
}

void AGCharacter::ShowPerimeter(bool Show)
{
	for (auto& p : Perimeters)
	{
		p->SetActorHiddenInGame(!Show);
	}
}

void AGCharacter::ShowShortestPath(bool Show)
{
	if (PathActor)
	{
		PathActor->SetActorHiddenInGame(!Show);
	}
}

void AGCharacter::DrawShortestPath(FTileIndex TileIndex)
{
	TArray<FVector> Points;
	UGridUtils::UnravelPath(Grid, ShortestPaths, TileIndex, Points);

	if (!PathActor)
	{
		PathActor = GetWorld()->SpawnActor<APath>(
			PathClass,
			GetActorLocation(),
			FRotator::ZeroRotator);
	}

	PathActor->DrawPath(Points);
	PathActor->SetActorHiddenInGame(true);
}

bool AGCharacter::TileInRange(FTile Tile)
{
	return int(ShortestPaths[Tile.Index].Distance) <= State->MovementSpeed;
}

void AGCharacter::HandleInput()
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

bool AGCharacter::RevertAction()
{
	if (ActionsBuffer.Num() > 0)
	{
		int Index = ActionsBuffer.Num() - 1;
		ActionsBuffer[Index]->RevertAction();
		ActionsBuffer.RemoveAt(Index);
		return true;
	}

	return false;
}

void AGCharacter::Selected()
{

}
