// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Grid/GridUtils.h"
#include "Grid/APerimeter.h"
#include "Grid/APath.h"
#include "GCharacter.generated.h"



UCLASS()
class TACTICALGAME_API AGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool IsMoving = false;

	FTile* CurrentTile;

	DijkstraOutput ShortestPaths;

	// Perimeters Data
	TArray<APerimeter*> Perimeters;

	UPROPERTY()
	APath* PathActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void Init(UPlayerInfo* PlayerInfo);
	bool IsInMeleeRange(AGCharacter* Enemy);
	bool IsInLineOfSight(AGCharacter* Enemy);
	void Shoot(AGCharacter* Enemy);
	void Melee(AGCharacter* Enemy);
	void GetDamage(float Damage);
	void MoveTo(FTile Tile);

	// Grid Path Methods
	void ComputeShortestPaths();
	void ComputePerimeterPoints(int TilesPerMovementAction);
	void ShowPerimeter(bool Show);
	void ShowShortestPath(bool Show);
	void DrawShortestPath(FTile* Tile);
};