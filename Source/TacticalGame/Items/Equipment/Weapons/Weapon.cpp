// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Items/Equipment/Weapons/WeaponCore.h"
#include "Components/SkeletalMeshComponent.h"



// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SnapToActor(AGCharacter* Character)
{
	AttachToComponent(
		Character->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true),
		TEXT("RightHandWeaponSocket"));
}

void AWeapon::ExecuteAttack()
{

}

void AWeapon::SetSimulationInfo(FRoundSim MyRound, AGCharacter* MyTarget)
{
	Target = MyTarget;
	Round = MyRound;
}