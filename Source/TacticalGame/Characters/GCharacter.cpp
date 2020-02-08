// Fill out your copyright notice in the Description page of Project Settings.


#include "GCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Globals/TacticalGameGameMode.h"
#include "Grid/GridUtils.h"
#include "Grid/ATileMapSet.h"
#include "GameFramework/SpringArmComponent.h"


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

	for (auto& pair : ShortestPaths)
	{
		UE_LOG(LogTemp, Warning, TEXT("result %s"), *pair.Value.Tile->ToString());
		//values.Add(pair.Value);
	}
}


void AGCharacter::ComputePerimeterPoints(int TilesPerMovementAction)
{
	TArray<FDijkstraNode*> values;

	for (auto& pair : ShortestPaths)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *pair.Value->Tile->ToString());
		values.Add(&pair.Value);
	}


	ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

	PerimeterPoints = UGridUtils::GetPerimeterPoints(
		values,
		TilesPerMovementAction,
		GameMode->GameDirector->TileMap->CellSize,
		GameMode->GameDirector->TileMap->PerimeterVOffset);
}

void AGCharacter::DrawPerimeter() 
{
	ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->GameDirector->TileMap->Drawer->DrawPerimeter(PerimeterPoints);
}