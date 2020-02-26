// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "APath.generated.h"

UCLASS()
class TACTICALGAME_API APath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APath();

	UPROPERTY()
	USplineComponent* Path;

	UPROPERTY()
	UStaticMesh* Mesh;

	TArray<USplineMeshComponent*> ArrowMeshes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DrawPath(TArray<FVector> Points);

};
