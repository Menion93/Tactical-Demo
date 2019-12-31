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

	APlayerCameraManager* CameraManager;
	APlayerController* PlayerController;
	UDecalComponent* GridCursor;
	UMaterialInterface* DecalMaterial;

	UPROPERTY()
	FTile SelectedTile;

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
		FTile GetTileFromNearestPosition(FVector NearestPos);
	
	void BuildGrid();
	FTile SnapToGrid(AActor* actor);
};