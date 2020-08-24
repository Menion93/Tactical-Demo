// Fill out your copyright notice in the Description page of Project Settings.


#include "GCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Globals/TacticalGameMode.h"
#include "Grid/Grid.h"
#include "GameFramework/SpringArmComponent.h"
#include "Grid/Cover.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
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

	UCapsuleComponent* caps = GetCapsuleComponent();
	caps->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);

	PathfindingComponent = CreateDefaultSubobject<UPathfindingComponent>(TEXT("Pathfinding Component"));
	PerimeterComponent = CreateDefaultSubobject<UPerimeterComponent>(TEXT("Perimeter Component"));
	LoSComponent = CreateDefaultSubobject<ULoSComponent>(TEXT("LoS Component"));

	// Camera setup
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-10.0f, -10.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 150;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AGCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
}

void AGCharacter::Init(AFireTeam* FT, UCharacterState* MyState)
{
	GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	Grid = GameMode->Grid;
	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());
	FireTeam = FT;
	State = MyState;

	PathfindingComponent->Init(this);
	PerimeterComponent->Init(Grid);

	State->Equipment->SpawnWeaponActor();
}

void AGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsMoving = !GetVelocity().IsZero();
}

void AGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGCharacter::ComputeShortestPaths()
{
	PathfindingComponent->ComputeShortestPaths(CurrentTileIndex, 9999);
}

void AGCharacter::ComputePerimeterPoints()
{
	PerimeterComponent->ComputePerimeterPoints(CurrentTileIndex, State->MovementSpeed);
}

void AGCharacter::ComputeLoS()
{
	LoSComponent->ComputeLoS(PathfindingComponent->ShortestPaths, this);
}

TArray<UAction*> AGCharacter::GetAdditionalActions()
{
	TArray<UAction*> AdditionalActions;
	return AdditionalActions;
}

TArray<UObject*> AGCharacter::GetOffensiveOptions()
{
	return State->Equipment->GetOffensiveItems();
}

TArray<UObject*> AGCharacter::GetSupportOptions()
{
	return State->Equipment->GetSupportItems();
}

void AGCharacter::HandleInput()
{
	if (!Input->LAxis.IsZero())
	{
		FVector Direction = FVector(Input->LAxis.X, Input->LAxis.Y, GetActorLocation().Z);
		AddMovementInput(Direction);

		if (Input->LAxis.X != 0 || Input->LAxis.Y != 0)
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
		if (ActionsBuffer[Index]->RevertAction())
		{
			ActionsBuffer.RemoveAt(Index);
			return true;
		}
	}
	return false;
}

void AGCharacter::Selected()
{

}

void AGCharacter::MyTakeDamage(FRoundSim RoundSim, UActionableAction* Action)
{
	ShowFloatingDamage(RoundSim.Damage, RoundSim.HasCritted, Action);

	int OldHealth = State->CurrentHealth;
	State->CurrentHealth = FMath::Max(0,int(State->CurrentHealth - RoundSim.Damage));

	if (State->CurrentHealth <= 0)
	{
		// Play Dead Animation
	}

	if (OldHealth > State->CurrentHealth)
	{
		// Play Get Damaged Animation
	}

}

bool AGCharacter::TileInRange(FTile Tile)
{
	return PathfindingComponent->TileInRange(Tile, State->MovementSpeed);
}