// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeaponActor.h"

AMeleeWeaponActor::AMeleeWeaponActor()
{

}



void AMeleeWeaponActor::Init(UMeleeWeapon* MyState)
{
	State = MyState;
}

void AMeleeWeaponActor::ExecuteAttack()
{
	Target->MyTakeDamage(Round, State->CurrentAction);
}