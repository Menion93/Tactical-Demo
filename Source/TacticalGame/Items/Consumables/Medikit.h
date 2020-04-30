// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Items/Consumables/Consumable.h"
#include "BattleSystem/Actions/Actionable.h"
#include "Medikit.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TACTICALGAME_API UMedikit : public UConsumable
{
	GENERATED_BODY()
	
public:
	UMedikit();



};
