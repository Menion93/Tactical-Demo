// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Globals/TacticalGameGameMode.h"
#include "Characters/ControllableCharacter.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnCharacters(bool SnapToGrid)
{

	ATacticalGameGameMode* GameMode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());
	TArray<UCharacterState*> Team = GameMode->Party->GetSelectedTeam();
	for (int pos = 0; pos < Team.Num(); pos++)
	{
		UWorld* World = GetWorld();

		if (World && Spawns.Num() > pos)
		{
			AControllableCharacter* Character = World->SpawnActor<AControllableCharacter>(
				Team[pos]->ActorCharacterClass, 
				Spawns[pos]->GetActorLocation(), 
				FRotator::ZeroRotator);

			Team[pos]->ActorCharacter = Character;

			if (SnapToGrid)
			{
				FTile* Tile = GameMode->GameDirector->TileMap->SnapToGrid(Character);
				Character->CurrentTile = Tile;
				Tile->Character = Character;
			}
		}
	}
}