// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utils/GridUtils.h"
#include "Grid/Perimeter.h"
#include "Grid/Path.h"
#include "BattleSystem/Actions/Actionable.h"
#include "Utils/Structs.h"
#include "Globals/GPlayerController.h"
#include "PerimeterComponent.h"
#include "PathfindingComponent.h"
#include "LoSComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Utils/SimStructs.h"
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

public:
	UPROPERTY(BlueprintReadWrite)
	AGrid* Grid;

	UPROPERTY(BlueprintReadWrite)
	ATacticalGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	AGPlayerController* Input;

	UPROPERTY(BlueprintReadWrite)
	AFireTeam* FireTeam;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPathfindingComponent* PathfindingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPerimeterComponent* PerimeterComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ULoSComponent* LoSComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* OurCameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* OurCamera;

public:
	// List of reversible actions done in the current turn
	UPROPERTY(BlueprintReadWrite)
	TArray<UAction*> ActionsBuffer;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	TArray<UAction*> GetAdditionalActions();

	UFUNCTION(BlueprintCallable)
	void ComputePerimeterPoints();

	UFUNCTION(BlueprintCallable)
	void ComputeShortestPaths();

	UFUNCTION(BlueprintCallable)
	void ComputeLoS();

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

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetSupportOptions();

	UFUNCTION(BlueprintCallable)
	void TakeRangedWeaponDamage(TArray<FBulletSim> BulletsFired);

	UFUNCTION(BlueprintCallable)
	bool TileInRange(FTile Tile);


};