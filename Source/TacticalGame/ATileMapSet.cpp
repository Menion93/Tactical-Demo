// Fill out your copyright notice in the Description page of Project Settings.

#include "ATileMapSet.h"
#include "Components/BoxComponent.h"
#include "TacticalGameGameMode.h"
#include "GameFramework/PlayerController.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "BattleGameState.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AATileMapSet::AATileMapSet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called when the game starts or when spawned
void AATileMapSet::BeginPlay()
{
	Super::BeginPlay();

	CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	PlayerController = GetWorld()->GetFirstPlayerController();

	BuildGrid();
}

void AATileMapSet::OnConstruction(const FTransform & Transform)
{
	for (auto Decal : DebugDecals)
	{
		Decal->DestroyComponent();
	}

	DebugDecals = TArray<UDecalComponent*>();

	BuildGrid();
}

// Build the WorldGrid in 3D dimension
void AATileMapSet::BuildGrid() {

	TilesMap = TMap<FVector2D, FTile>();
	Height = Rows * CellSize;
	Width = Columns * CellSize;


	FVector ActorLocation = GetActorLocation();

	FVector OffsetVector = FVector(
		(Height * 0.5) * (1 - 1.0 / Rows),
		-(Width * 0.5) * (1 - 1.0 / Columns),
		0);

	for (int CurrRow = 0; CurrRow < Rows; CurrRow++)
	{
		for (int CurrCol = 0; CurrCol < Columns; CurrCol++)
		{
			FVector LocalTileCenter = FVector(-CurrRow * CellSize, CurrCol * CellSize, 0) + OffsetVector;
			FVector WTileCenter = GetActorRotation().RotateVector(LocalTileCenter) + ActorLocation;

			FTile MyTile;
			MyTile.TileCenter = WTileCenter;

			FHitResult OutHit;
			FCollisionQueryParams CollisionParams;

			TArray<FHitResult> OutHits;


			bool hit = GetWorld()->LineTraceMultiByChannel(
				OutHits,
				WTileCenter,
				WTileCenter - GetActorUpVector() * 1000,
				ECollisionChannel::ECC_GameTraceChannel1,
				CollisionParams);

			if (hit)
			{
				for (auto OutHit : OutHits) 
				{
					if (OutHit.bBlockingHit)
					{
						MyTile.TileCenter = OutHit.ImpactPoint;
						MyTile.SurfaceNormal = OutHit.ImpactNormal;

						FVector2D TileCenterKey(CurrRow, CurrCol);
						TilesMap.Add(TileCenterKey, MyTile);

						#if WITH_EDITOR
						if (DrawLinesInEditor)
						{
							 UDecalComponent* Decal = UGameplayStatics::SpawnDecalAttached(
								 DecalMaterial,
								 FVector(16.0f, 32.0f, 32.0f), 
								 OutHit.GetComponent(), 
								 OutHit.BoneName,
								 OutHit.ImpactPoint, 
								 OutHit.ImpactNormal.Rotation(), 
								 EAttachLocation::KeepWorldPosition,
								999);

							 DebugDecals.Add(Decal);
						}
						#endif
					}
					else
					{
						break;
					}
				}
			}

		}
	}

	// Now link cells

	FVector2D OffSetU(1, 0);
	FVector2D OffSetL(0, 1);
	FVector2D OffSetIQuad(1, 1);
	FVector2D OffSet2Quad(-1, 1);

	TArray<FVector2D> Neighbour;
	Neighbour.Add(OffSetU);
	Neighbour.Add(OffSetL);
	Neighbour.Add(OffSetIQuad);
	Neighbour.Add(OffSet2Quad);

	for (auto& tile : TilesMap)
	{
		for (int j = 0; j < 2; j++)
		{
			for (auto OffSetVec : Neighbour)
			{
				FVector2D NeighbourKey = tile.Key + (-j) * OffSetVec + (1 - j) * OffSetVec;

				if (TilesMap.Contains(NeighbourKey))
				{
					tile.Value.Neighbours.Emplace(&TilesMap[NeighbourKey]);
				}
			}
		}
	}

}

// Called every frame
void AATileMapSet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABattleGameState* gs = GetWorld()->GetGameState<ABattleGameState>();

	if (gs && gs->GridEnabled)
	{

		GridCursor->SetVisibility(true);

		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);

		if (Hit.bBlockingHit)
		{
			SelectedTile = GetTileFromNearestPosition(Hit.ImpactPoint);

			GridCursor->SetWorldLocationAndRotation(
				SelectedTile.TileCenter,
				SelectedTile.SurfaceNormal.ToOrientationRotator().Quaternion());
		}
	}
	else
	{
		GridCursor->SetVisibility(false);
	}
}



// Get the nearest tile from 
FTile AATileMapSet::GetTileFromNearestPosition(FVector NearestPos)
{
	float CurrDistance = 99999999;
	FTile NearestTile;

	for (auto tile : TilesMap)
	{
		float Distance = FVector::Distance(tile.Value.TileCenter, NearestPos);

		if (Distance < CurrDistance)
		{
			CurrDistance = Distance;
			NearestTile = tile.Value;
		}
	}

	return NearestTile;
}

FTile AATileMapSet::SnapToGrid(AActor* Actor)
{
	FTile Tile = GetTileFromNearestPosition(Actor->GetActorLocation());
	Actor->SetActorLocation(Tile.TileCenter);
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

