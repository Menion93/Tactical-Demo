// Fill out your copyright notice in the Description page of Project Settings.

#include "ATileMapSet.h"
#include "Components/BoxComponent.h"
#include "Globals/TacticalGameGameMode.h"
#include "GameFramework/PlayerController.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Utils/GridUtils.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AATileMapSet::AATileMapSet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Box to place the grid
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxGrid"));
	BoxComponent->SetBoxExtent(FVector(Height, Width, VerticalHeight));

	BoxComponent->SetupAttachment(RootComponent);

	// Create Decal
	GridCursor = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	GridCursor->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/Grid_Decal_Debug.Grid_Decal_Debug'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialDebug(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));

	DecalMaterial = DecalMaterialDebug.Object;

	if (DecalMaterialAsset.Succeeded())
	{
		GridCursor->SetDecalMaterial(DecalMaterialAsset.Object);
	}

	GridCursor->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	GridCursor->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	Path = CreateDefaultSubobject<USplineComponent>("Path");
	Path->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AATileMapSet::BeginPlay()
{
	Super::BeginPlay();

	CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	PlayerController = GetWorld()->GetFirstPlayerController();

	UGridUtils::BuildGrid(this,
		TilesMap,
		DebugDecals,
		DecalMaterial,
		Rows,
		Columns,
		CellSize,
		DrawLinesInEditor);
}

void AATileMapSet::OnConstruction(const FTransform & Transform)
{
	for (auto Decal : DebugDecals)
	{
		Decal->DestroyComponent();
	}

	DebugDecals = TArray<UDecalComponent*>();

	//UGridUtils::BuildGrid(this,
	//	TilesMap,
	//	DebugDecals,
	//	DecalMaterial,
	//	Rows,
	//	Columns,
	//	CellSize,
	//	DrawLinesInEditor);
}


// Called every frame
void AATileMapSet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Get the nearest tile from 
FTile* AATileMapSet::GetTileFromNearestPosition(FVector NearestPos)
{
	float CurrDistance = 99999999;
	FTile* NearestTile = nullptr;

	for (auto& tile : TilesMap)
	{
		float Distance = FVector::Distance(tile.Value.TileCenter, NearestPos);

		if (Distance < CurrDistance)
		{
			CurrDistance = Distance;
			NearestTile = &tile.Value;
		}
	}

	return NearestTile;
}

FTile* AATileMapSet::SnapToGrid(AGCharacter* Character)
{
	Character->GetActorLocation();
	FTile* Tile = GetTileFromNearestPosition(Character->GetActorLocation());
	Character->SetActorLocation(Tile->TileCenter + FVector::UpVector * Character->GetDefaultHalfHeight());
	Character->CurrentTile = Tile;
	Tile->Character = Character;
	return Tile;
}

void AATileMapSet::BeginDestroy() 
{
	Super::BeginDestroy();

	for (auto Decal : DebugDecals)
	{
		Decal->DestroyComponent();
	}
}

void AATileMapSet::SetCursorToTile(FTile* Tile)
{
	GridCursor->SetWorldLocationAndRotation(
		Tile->TileCenter,
		Tile->SurfaceNormal.ToOrientationRotator().Quaternion());
}

void AATileMapSet::ShowCursor(bool show)
{
	GridCursor->SetVisibility(show);
}