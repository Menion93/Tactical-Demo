// Fill out your copyright notice in the Description page of Project Settings.
#include "APerimeter.h"
#include "SceneManagement.h"
#include "Globals/TacticalGameGameMode.h"
#include "Engine/World.h"
#include "Grid/ATileMapSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StreamableManager.h"
#include "DrawDebugHelpers.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"


APerimeter::APerimeter()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Meshes/line.line'"));
	Mesh = MeshAsset.Object;

	Perimeter = CreateDefaultSubobject<USplineComponent>("Perimeter");
	Perimeter->SetupAttachment(RootComponent);
}

void APerimeter::DrawPerimeter(TArray<FVector> Points)
{
	Perimeter->ClearSplinePoints();

	for (auto p : Points)
	{
		Perimeter->AddSplinePoint(p + FVector::UpVector * 50, ESplineCoordinateSpace::World, true);
	}

	Perimeter->AddSplinePoint(Points[0] + FVector::UpVector * 50, ESplineCoordinateSpace::World, true);


	for (int i = 0; i < Perimeter->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* MeshComp = NewObject<USplineMeshComponent>(this);

		FVector Position;
		FVector Tangent;
		Perimeter->GetLocationAndTangentAtSplinePoint(i, Position, Tangent, ESplineCoordinateSpace::World);

		FVector Position2;
		FVector Tangent2;
		Perimeter->GetLocationAndTangentAtSplinePoint(i + 1, Position2, Tangent2, ESplineCoordinateSpace::World);

		MeshComp->SetStaticMesh(Mesh);
		MeshComp->SetForwardAxis(ESplineMeshAxis::X, true);
		MeshComp->SetStartAndEnd(Position, Tangent*0.1, Position2, Tangent2 *0.1);
		
		MeshComp->SetStartScale(FVector2D(0.3, 1));
		MeshComp->SetEndScale(FVector2D(0.3, 1));
		
		MeshComp->RegisterComponent();
		MeshComp->SetCastShadow(false);

		//MeshComp->AttachTo(GetDefaultAttachComponent(), TEXT(""), EAttachLocation::KeepWorldPosition, true);
	}
}
