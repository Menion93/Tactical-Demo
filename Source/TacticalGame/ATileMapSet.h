// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TacticalGameGameMode.h"
#include "ATileMapSet.generated.h"


USTRUCT()
struct FTile
{
	GENERATED_BODY()
		bool IsObstacle = false;
		FVector TileCenter = FVector(0, 0, 0);
		FVector SurfaceNormal = FVector(0, 0, 0);
		bool IsCover = false;
};

UCLASS()
class TACTICALGAME_API AATileMapSet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATileMapSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		bool IsSquare;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		int Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		int Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		float VerticalHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorSetting")
		bool DrawLinesInEditor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorSetting")
		float LineLength;

	ATacticalGameGameMode* Mode;
	APlayerCameraManager* CameraManager;
	APlayerController* PlayerController;
	UDecalComponent* GridCursor;
	UMaterialInterface* DecalMaterial;

	UPROPERTY()
	FTile CurrentTile;


	float Height;
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "TileSettings")
		TMap<FVector2D, FTile> TilesMap;

	TArray<UDecalComponent*> DebugDecals;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform & Transform);
	virtual void BeginDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FTile GetTileFromNearestPosition(FVector& NearestPos);
	
	void BuildGrid();

	
};