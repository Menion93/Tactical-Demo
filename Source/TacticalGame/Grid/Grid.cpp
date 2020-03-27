// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"
#include "Components/BoxComponent.h"
#include "Globals/TacticalGameMode.h"
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
AGrid::AGrid()
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

	GridCursor->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	GridCursor->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	PlayerController = GetWorld()->GetFirstPlayerController();

	GridCursor->SetDecalMaterial(DecalMaterial);

	UGridUtils::BuildGrid(this,
		TilesMap,
		DebugDecals,
		DecalMaterialDebug,
		Rows,
		Columns,
		CellSize,
		DrawLinesInEditor);
}

void AGrid::OnConstruction(const FTransform & Transform)
{
	for (auto Decal : DebugDecals)
	{
		Decal->DestroyComponent();
	}

	DebugDecals = TArray<UDecalComponent*>();

	//UGridUtils::BuildGrid(this,
	//	TilesMap,
	//	DebugDecals,
	//	DecalMaterialDebug,
	//	Rows,
	//	Columns,
	//	CellSize,
	//	DrawLinesInEditor);
}


// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Get the nearest tile from 
FTile* AGrid::GetTileFromNearestPosition(FVector NearestPos)
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

FTile* AGrid::SnapToGrid(AGCharacter* Character)
{
	Character->GetActorLocation();
	FTile* Tile = GetTileFromNearestPosition(Character->GetActorLocation());
	Character->SetActorLocation(Tile->TileCenter + FVector::UpVector * Character->GetDefaultHalfHeight());
	Character->CurrentTileIndex = Tile->Index;
	Tile->Character = Character;
	return Tile;
}

void AGrid::BeginDestroy()
{
	Super::BeginDestroy();

	for (auto Decal : DebugDecals)
	{
		Decal->DestroyComponent();
	}
}

void AGrid::SetCursorToTile(FTileIndex TileIndex)
{
	FTile Tile = TilesMap[TileIndex];
	GridCursor->SetWorldLocationAndRotation(
		Tile.TileCenter,
		Tile.SurfaceNormal.ToOrientationRotator().Quaternion());
}

void AGrid::ShowCursor(bool show)
{
	GridCursor->SetVisibility(show);
}

void AGrid::TransferCharacterToTile(FTileIndex From, FTileIndex To)
{
	if (!TilesMap.Contains(From) || !TilesMap.Contains(To))
	{
		return;
	}

	FTile FromTile = TilesMap[From];
	FTile ToTile = TilesMap[To];

	if (!FromTile.Character) return;
	if (ToTile.Character) return;

	ToTile.Character = FromTile.Character;
	FromTile.Character = nullptr;

	TilesMap[FromTile.Index] = FromTile;
	TilesMap[ToTile.Index] = ToTile;
}

FTile AGrid::GetTile(FTileIndex TileIndex)
{
	return TilesMap[TileIndex];
}
