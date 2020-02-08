// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridDrawer.generated.h"

class AATileMapSet;
/**
 * 
 */
UCLASS()
class TACTICALGAME_API UGridDrawer : public UObject
{
	GENERATED_BODY()
	
public:
	UGridDrawer();

	AATileMapSet* TileMap;

public:
	void Init(AATileMapSet* TileMapRef);

	void DrawPerimeter(TArray<FVector> Points);
	void DrawPath(TArray<FVector> Path);

};
