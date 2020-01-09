// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FTile.h"
#include "ATileMapSet.generated.h"



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

	UPROPERTY()
	APlayerCameraManager* CameraManager;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UDecalComponent* GridCursor;

	UPROPERTY()
	UMaterialInterface* DecalMaterial;

	float Height;
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSettings")
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "TileSettings")
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
	FTile* SnapToGrid(AActor* actor);

	void BuildGrid();
	void SetCursorToTile(FTile* Tile);
	void ShowCursor(bool show);
};