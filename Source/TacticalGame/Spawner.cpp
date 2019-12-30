// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "TacticalGameGameMode.h"
#include "ControllableCharacter.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AControllableCharacter> Player1(TEXT("/Game/TopDownCPP/Blueprints/Characters/Player1"));
	static ConstructorHelpers::FClassFinder<AControllableCharacter> Player2(TEXT("/Game/TopDownCPP/Blueprints/Characters/Player2"));

	if (Player1.Class != NULL)
	{
		party.Add(Player1.Class);
	}

	if (Player2.Class != NULL)
	{
		party.Add(Player2.Class);
	}
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
	for (int pos = 0; pos < party.Num(); pos++)
	{
		UWorld* World = GetWorld();

		if (World && Spawns.Num() > pos)
		{
			AControllableCharacter* character = World->SpawnActor<AControllableCharacter>(party[pos], Spawns[pos]->GetActorLocation(), FRotator::ZeroRotator);
			ATacticalGameGameMode* GM = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());

			if (SnapToGrid)
			{
				GM->GameDirector->TileMap->SnapToGrid(character);
			}
		}
	}
}