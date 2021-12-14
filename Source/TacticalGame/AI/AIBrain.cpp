// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIBrain.h"

UAIBrain::UAIBrain() {}

void UAIBrain::Init_Implementation(AGCharacter* mOwner, ATacticalGameMode* GM)
{
	Owner = mOwner;
	GameMode = GM;
}