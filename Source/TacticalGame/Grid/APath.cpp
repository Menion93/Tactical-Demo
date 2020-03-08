// Fill out your copyright notice in the Description page of Project Settings.


#include "APath.h"
#include "SceneManagement.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StreamableManager.h"


// Sets default values
APath::APath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Meshes/line.line'"));
	Mesh = MeshAsset.Object;

	Path = CreateDefaultSubobject<USplineComponent>("Path");
	Path->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APath::DrawPath(TArray<FVector> Points) 
{

	Path->ClearSplinePoints();

	for (auto& mesh : ArrowMeshes) 
	{
		mesh->DestroyComponent();
	}

	ArrowMeshes = TArray<USplineMeshComponent*>();

	for (auto p : Points)
	{
		Path->AddSplinePoint(p + FVector::UpVector * 50, ESplineCoordinateSpace::World, true);
	}

	for (int i = 0; i < Path->GetNumberOfSplinePoints() - 1; i++)
	{
		USplineMeshComponent* MeshComp = NewObject<USplineMeshComponent>(this);

		FVector Position;
		FVector Tangent;
		Path->GetLocationAndTangentAtSplinePoint(i, Position, Tangent, ESplineCoordinateSpace::World);

		FVector Position2;
		FVector Tangent2;
		Path->GetLocationAndTangentAtSplinePoint(i + 1, Position2, Tangent2, ESplineCoordinateSpace::World);

		MeshComp->SetStaticMesh(Mesh);
		MeshComp->SetForwardAxis(ESplineMeshAxis::X, true);
		MeshComp->SetStartAndEnd(Position, Tangent*0.1, Position2, Tangent2 *0.1);

		MeshComp->SetStartScale(FVector2D(0.3, 1));
		MeshComp->SetEndScale(FVector2D(0.3, 1));

		MeshComp->RegisterComponent();
		MeshComp->SetCastShadow(false);

		//MeshComp->AttachTo(GetDefaultAttachComponent(), TEXT(""), EAttachLocation::KeepWorldPosition, true);
		ArrowMeshes.Add(MeshComp);
	}
}

