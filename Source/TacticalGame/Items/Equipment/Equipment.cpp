// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Characters/CharacterState.h"


UEquipment::UEquipment()
{

}

void UEquipment::LoadDefaultEquipment(UCharacterState* MyState)
{
	State = MyState;

	if (PrimaryWeaponClass)
	{
		PrimaryWeapon = NewObject<UWeaponCore>(this, PrimaryWeaponClass);
		PrimaryWeapon->InitWeapon();
		CurrentWeapon = PrimaryWeapon;
	}

	if (SecondaryWeaponClass)
	{
		SecondaryWeapon = NewObject<UWeaponCore>(this, SecondaryWeaponClass);
		SecondaryWeapon->InitWeapon();
	}

	if (ArmorClass)
	{
		Armor = NewObject<UArmor>(this, ArmorClass);
	}

	if (ShieldClass)
	{
		Shield = NewObject<UShield>(this, ShieldClass);
		Shield->InitShield();
	}

}

TArray<UObject*> UEquipment::GetSupportItems()
{
	TArray<UObject*> SupportItems = TArray<UObject*>();

	UObject* SupportWeapon = TryGetObjectByType(Cast<UItem>(PrimaryWeapon), ActionType::SUPPORT);

	if (SupportWeapon)
	{
		SupportItems.Add(SupportWeapon);
	}

	SupportWeapon = TryGetObjectByType(Cast<UItem>(SecondaryWeapon), ActionType::SUPPORT);

	if (SupportWeapon)
	{
		SupportItems.Add(SupportWeapon);
	}

	return SupportItems;
}

TArray<UObject*> UEquipment::GetOffensiveItems()
{
	TArray<UObject*> OffensiveItems = TArray<UObject*>();

	UObject* OffensiveWeapon = TryGetObjectByType(Cast<UItem>(PrimaryWeapon), ActionType::OFFENSIVE);

	if (OffensiveWeapon)
	{
		OffensiveItems.Add(OffensiveWeapon);
	}

	OffensiveWeapon = TryGetObjectByType(Cast<UItem>(SecondaryWeapon), ActionType::OFFENSIVE);

	if (OffensiveWeapon)
	{
		OffensiveItems.Add(OffensiveWeapon);
	}
	
	return OffensiveItems;
}

UObject* UEquipment::TryGetObjectByType(UItem* Item, ActionType Type)
{
	IActionable* ActionabeItem = Cast<IActionable>(Item);

	if (ActionabeItem)
	{
		if(ActionabeItem->Execute_GetActionType(Item) == Type)
		{
			return Cast<UObject>(ActionabeItem);
		}
	}

	return nullptr;
}

void UEquipment::SwapWeapon()
{
	if (FirstWeaponEquipped)
	{
		if (SecondaryWeapon)
		{
			PrimaryWeapon->DestoryWeaponActor();
			CurrentWeapon = SecondaryWeapon;
			CurrentWeapon->SpawnWeaponActor(State->ActorCharacter);
			FirstWeaponEquipped = false;
		}
	}
	else
	{
		SecondaryWeapon->DestoryWeaponActor();
		CurrentWeapon = PrimaryWeapon;
		CurrentWeapon->SpawnWeaponActor(State->ActorCharacter);
		FirstWeaponEquipped = true;
	}

	OnSwapWeapon.Broadcast();
}

void UEquipment::SpawnWeaponActor()
{
	if (PrimaryWeapon)
	{
		CurrentWeapon = PrimaryWeapon;
		CurrentWeapon->SpawnWeaponActor(State->ActorCharacter);
	}
}
