// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FTile.h"
#include "Characters/GCharacter.h"
#include "Components/SplineComponent.h"
#include "Grid.generated.h"

UCLASS(Blueprintable)
class TACTICALGAME_API AGrid : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGrid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	bool IsSquare;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	int Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	int Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	float PerimeterVOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	float VerticalHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorSetting")
		bool DrawLinesInEditor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorSetting")
		float LineLength;

	UPROPERTY()
	APlayerCameraManager* CameraManager;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UDecalComponent* GridCursor;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DecalMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DecalMaterialDebug;

	float Height;
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
	TMap<FTileIndex, FTile> TilesMap;

	TArray<UDecalComponent*> DebugDecals;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform & Transform);
	virtual void BeginDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FTile* GetTileFromNearestPosition(FVector NearestPos);
	FTile* SnapToGrid(AGCharacter* actor);
	
	UFUNCTION(BlueprintCallable)
	void TransferCharacterToTile(FTileIndex From, FTileIndex To);

	UFUNCTION(BlueprintCallable)
	void SetCursorToTile(FTileIndex TileIndex);

	UFUNCTION(BlueprintCallable)
	void ShowCursor(bool show);

	UFUNCTION(BlueprintCallable)
	FTile GetTile(FTileIndex TileIndex);
};