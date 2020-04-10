// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

UENUM(BlueprintType)
enum class CoverTypeE : uint8
{
	PARTIAL UMETA(DisplayName = "Partial Cover"),
	TOTAL UMETA(DisplayName = "Full Cover"),
	NONE UMETA(DisplayName = "No Cover")

};

UCLASS(Blueprintable)
class TACTICALGAME_API ACover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CoverTypeE Cover;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual CoverTypeE GetCoverType();

};
