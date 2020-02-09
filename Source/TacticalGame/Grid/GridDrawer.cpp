// Fill out your copyright notice in the Description page of Project Settings.


#include "GridDrawer.h"
#include "SceneManagement.h"
#include "ATileMapSet.h"


UGridDrawer::UGridDrawer()
{

}

void UGridDrawer::Init(AATileMapSet* TileMapRef)
{
	TileMap = TileMapRef;
}


void UGridDrawer::DrawPerimeter(TArray<FVector> Points)
{
	for (auto p : Points)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *p.ToString())
	}
}


void UGridDrawer::DrawPath(TArray<FVector> Path)
{

}

