// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UAction : public UObject
{
	GENERATED_BODY()
	
public:
	UAction();

public:
	bool PlayAction();

};
