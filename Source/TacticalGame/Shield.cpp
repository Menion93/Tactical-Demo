// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

// Sets default values
UShield::UShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UShield::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UShield::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

