// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPath.h"

// Sets default values
AGridPath::AGridPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

