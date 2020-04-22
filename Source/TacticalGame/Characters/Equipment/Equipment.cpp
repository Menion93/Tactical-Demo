// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"


UEquipment::UEquipment()
{

}

void UEquipment::LoadDefaultEquipment()
{
	if (PrimaryWeaponClass)
	{
		PrimaryWeapon = NewObject<UWeaponCore>(this, PrimaryWeaponClass);
	}

	if (SecondaryWeaponClass)
	{
		SecondaryWeapon = NewObject<UWeaponCore>(this, SecondaryWeaponClass);
	}

	if (BagClass)
	{
		Bag = NewObject<UBag>(this, BagClass);
	}

	if (ArmorClass)
	{
		Armor = NewObject<UArmor>(this, ArmorClass);
	}

	if (ShieldClass)
	{
		Shield = NewObject<UShield>(this, ShieldClass);
	}

}

TArray<UObject*> UEquipment::GetSupportItems()
{
	TArray<UObject*> SupportItems = Bag->GetSupportItems();

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
	TArray<UObject*> OffensiveItems = Bag->GetOffensiveItems();

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
