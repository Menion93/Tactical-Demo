// Fill out your copyright notice in the Description page of Project Settings.


#include "GCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Globals/TacticalGameGameMode.h"
#include "Grid/ATileMapSet.h"
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

void AGCharacter::MoveTo(FTile Tile)
{

}

void AGCharacter::ComputeShortestPaths()
{
	UGridUtils::GetShortestPaths(ShortestPaths, CurrentTile, 9999);
}


void AGCharacter::ComputePerimeterPoints(int TilesPerMovementAction)
{
	ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

	TArray<FVectorArray> PerimeterBlocks = UGridUtils::GetPerimeterPoints(
		ShortestPaths,
		TilesPerMovementAction,
		GameMode->GameDirector->TileMap->CellSize,
		GameMode->GameDirector->TileMap->PerimeterVOffset);

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
	for (auto p : Perimeters)
	{
		p->SetActorHiddenInGame(!Show);
	}
}

void AGCharacter::ShowShortestPath(bool Show)
{
	PathActor->SetActorHiddenInGame(!Show);
}

void AGCharacter::DrawShortestPath(FTile* Tile)
{
	FDijkstraNode* node = &ShortestPaths[Tile->Index];

	// If tile is the actor's tile, dont do anything
	if (!ShortestPaths.Contains(node->Prev))
	{
		return;
	}

	TArray<FVector> Points;

	while (ShortestPaths.Contains(node->Prev))
	{
		Points.Add(node->Tile->TileCenter);
		node = &ShortestPaths[node->Prev];
	}

	Points.Add(node->Tile->TileCenter);

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