// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utils/GridUtils.h"
#include "Grid/Perimeter.h"
#include "Grid/Path.h"
#include "Interfaces/OffensiveOption.h"
#include "Utils/Structs.h"
#include "Globals/GPlayerController.h"
#include "GCharacter.generated.h"

class UCharacterState;
class AGrid;
class ATacticalGameMode;

UCLASS()
class TACTICALGAME_API AGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGCharacter();

	UPROPERTY(BlueprintReadWrite)
	UCharacterState* State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UCharacterState> StateClass;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex CurrentTileIndex;

	UPROPERTY(BlueprintReadWrite)
	AGrid* Grid;

	UPROPERTY(BlueprintReadWrite)
	ATacticalGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	AFireTeam* FireTeam;

	///////////////////// Perimeters and Path
	TArray<APerimeter*> Perimeters;

	UPROPERTY()
	APath* PathActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APath> PathClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APerimeter> PerimeterClass;

	///////////////// PATHFINDING
	// Used for steering to next point during pathfinding
	UPROPERTY(BlueprintReadWrite)
	TMap<FTileIndex, FDijkstraNode> ShortestPaths;

	UPROPERTY(BlueprintReadWrite)
	TMap<FTileIndex, FDijkstraNode> PerimeterBoundaries;

	UPROPERTY(EditAnywhere)
	float ToleranceBetweetCkpts = 1;

	// Used for pathfinding
	TArray<FVector> MovePoints;
	int PathIndex = -1;

	AGPlayerController* Input;

	// List of reversible actions done in the current turn
	TArray<UAction*> ActionsBuffer;

	// Line of Sights Computations
	TMap<FName, FLineOfSights> LoS;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool MoveTo(FTileIndex TileIndex);

	UFUNCTION(BlueprintCallable)
	bool TileInRange(FTile Tile);

	// Grid Path Methods
	UFUNCTION(BlueprintCallable)
	void ComputeShortestPaths();

	UFUNCTION(BlueprintCallable)
	void ComputePerimeterPoints();

	UFUNCTION(BlueprintCallable)
	void ComputeLoS();

	UFUNCTION(BlueprintCallable)
	void ShowPerimeter(bool Show);

	UFUNCTION(BlueprintCallable)
	void ShowShortestPath(bool Show);

	UFUNCTION(BlueprintCallable)
	void DrawShortestPath(FTileIndex TileIndex);

	UFUNCTION(BlueprintCallable)
	TArray<UAction*> GetAdditionalActions();

	UFUNCTION(BlueprintCallable)
	void HandleInput();

	UFUNCTION(BlueprintCallable)
	void Selected();

	UFUNCTION(BlueprintCallable)
	void Init(AFireTeam* FT);

	UFUNCTION(BlueprintCallable)
	bool RevertAction();

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetOffensiveOptions();


private:
	void AddLoS(
		AGCharacter* Character,
		FTile& Tile,
		CoverTypeE Cover,
		float Distance);

};