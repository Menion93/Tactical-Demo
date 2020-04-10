// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCore.h"


// Sets default values for this component's properties
UWeaponCore::UWeaponCore()
{

}

bool UWeaponCore::IsInRange(AGCharacter* MyCharacter, AGCharacter* Target)
{
	return false;
}

bool UWeaponCore::IsInRangeFromCurrentPosition(AGCharacter* MyCharacter, AGCharacter* Target)
{
	return false;
}

void UWeaponCore::SimulateAttack(AGCharacter* Character, AGCharacter* Target)
{

}

void UWeaponCore::ApplyAttack(AGCharacter* Target)
{

}

void UWeaponCore::Attack(AGCharacter* Character, AGCharacter* Target)
{
	SimulateAttack(Character, Target);
	ApplyAttack(Target);
}

bool UWeaponCore::CanAttackEnemy_Implementation(AGCharacter* Character, AGCharacter* Target)
{
	return false;
}

