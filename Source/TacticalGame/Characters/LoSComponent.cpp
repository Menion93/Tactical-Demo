// Fill out your copyright notice in the Description page of Project Settings.


#include "LoSComponent.h"
#include "CharacterState.h"
#include "Globals/TacticalGameMode.h"
#include "GCharacter.h"
#include "BattleSystem/FireTeam.h"

// Sets default values for this component's properties
ULoSComponent::ULoSComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TMap<FName, FLineOfSights> ULoSComponent::GetLoS()
{
	return LoS;
}


void ULoSComponent::ComputeLoS(TMap<FTileIndex, FDijkstraNode>& ShortestPaths, AGCharacter* Subject)
{
	TArray<FDijkstraNode> Nodes;
	ShortestPaths.GenerateValueArray(Nodes);

	Nodes = Nodes.FilterByPredicate([Subject](auto& Node) {
		return int(Node.Distance) <= Subject->State->MovementSpeed;
	});

	LoS = TMap<FName, FLineOfSights>();

	TArray<AFireTeam*> FTeams = Subject->GameMode->BattleManager->GetHostileFireTeams(Subject->FireTeam);

	for (auto& Node : Nodes)
	{
		for (auto& FT : FTeams)
		{
			for (auto& Character : FT->Characters)
			{
				FTile Tile = Subject->Grid->GetTile(Node.TileIndex);

				FCollisionQueryParams CollisionParams;

				TArray<FHitResult> OutHits;

				bool hit = GetWorld()->LineTraceMultiByChannel(
					OutHits,
					Tile.TileCenter + FVector::UpVector * Subject->GetDefaultHalfHeight(),
					Character->GetActorLocation(),
					ECollisionChannel::ECC_GameTraceChannel2,
					CollisionParams);

				CoverTypeE Cover = CoverTypeE::NONE;
				for (auto& OutHit : OutHits)
				{
					if (!OutHit.bBlockingHit)
					{
						AGCharacter* HitChar = Cast<AGCharacter>(OutHit.Actor);

						// LoS found
						if (HitChar != Subject && HitChar != Character)
						{
							ACover* CoverObj = Cast<ACover>(OutHit.Actor);

							if (CoverObj)
							{
								Cover = CoverObj->GetCoverType();
							}
							else
							{
								break;
							}
						}
						else if (HitChar == Character)
						{
							AddLoS(Character, Tile, Cover, OutHit.Distance);
						}
						else if (HitChar == Subject)
						{
							continue;
						}
					}
				}
			}
		}
	}
}


void ULoSComponent::AddLoS(
	AGCharacter* Character,
	FTile& Tile,
	CoverTypeE Cover,
	float Distance)
{	
	FName CharacterName(Character->GetName());

	if (!LoS.Contains(CharacterName))
	{
		LoS.Add(CharacterName, FLineOfSights());
	}

	FLineOfSights* LinesOfSights = LoS.Find(CharacterName);

	LinesOfSights->Tiles.Add(Tile.Index, FLineOfSight(Cover, Distance));
}

