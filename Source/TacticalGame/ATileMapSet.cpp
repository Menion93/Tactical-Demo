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

	Mode = Cast<ATacticalGameGameMode>(GetWorld()->GetAuthGameMode());
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
		(Height * 0.5) * (1 - (1 / (float)Rows)),
		-(Width * 0.5) * (1 - 1 / ((float)Columns)),
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
						FVector2D TileCenterKey(OutHit.ImpactPoint.X, OutHit.ImpactPoint.Y);
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
}

// Called every frame
void AATileMapSet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABattleGameState* gs = GetWorld()->GetGameState<ABattleGameState>();

	//UE_LOG(LogTemp, Warning, TEXT("%d"), gs == nullptr);
	if (gs && gs->GridEnabled)
	{

		GridCursor->SetVisibility(true);

		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);

		if (Hit.bBlockingHit)
		{
			CurrentTile = GetTileFromNearestPosition(Hit.ImpactPoint);

			GridCursor->SetWorldLocationAndRotation(
				CurrentTile.TileCenter,
				CurrentTile.SurfaceNormal.ToOrientationRotator().Quaternion());
		}
	}
	else
	{
		GridCursor->SetVisibility(false);
	}
}



// Get the nearest tile from 
FTile AATileMapSet::GetTileFromNearestPosition(FVector &NearestPos)
{
	float CurrDistance = 99999999;
	FTile NearestTile;

	for (auto tile : TilesMap)
	{
		FVector2D NearestPos2D(NearestPos.X, NearestPos.Y);
		float Distance = FVector2D::Distance(tile.Key, NearestPos2D);

		if (Distance < CurrDistance)
		{
			CurrDistance = Distance;
			NearestTile = tile.Value;
		}
	}

	return NearestTile;
}

void AATileMapSet::BeginDestroy() 
{
	Super::BeginDestroy();

	for (auto Decal : DebugDecals)
	{
		Decal->DestroyComponent();
	}
}

