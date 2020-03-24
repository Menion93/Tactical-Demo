// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utils/GridUtils.h"
#include "Grid/APerimeter.h"
#include "Grid/APath.h"
#include "GCharacter.generated.h"

class UCharacterState;
class AATileMapSet;

UCLASS()
class TACTICALGAME_API AGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterState* State;

	UPROPERTY(BlueprintReadWrite)
	FTileIndex CurrentTileIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	AATileMapSet* TileMap;

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

	UPROPERTY(EditAnywhere)
	float ToleranceBetweetCkpts = 1;

	// Used for pathfinding
	TArray<FVector> MovePoints;
	int PathIndex = -1;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void Init(UPlayerInfo* PlayerInfo);
	UFUNCTION(BlueprintCallable)
	bool IsInMeleeRange(AGCharacter* Enemy);

	UFUNCTION(BlueprintCallable)
	bool IsInLineOfSight(AGCharacter* Enemy);

	UFUNCTION(BlueprintCallable)
	void Shoot(AGCharacter* Enemy);

	UFUNCTION(BlueprintCallable)
	void Melee(AGCharacter* Enemy);

	UFUNCTION(BlueprintCallable)
	void GetDamage(float Damage);

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
	void ShowPerimeter(bool Show);

	UFUNCTION(BlueprintCallable)
	void ShowShortestPath(bool Show);

	UFUNCTION(BlueprintCallable)
	void DrawShortestPath(FTileIndex TileIndex);
};