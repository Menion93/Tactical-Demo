// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Interfaces/OffensiveOption.h"

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

TArray<UObject*> UEquipment::GetOffensiveItems()
{
	TArray<UObject*> OffensiveItems = Bag->GetOffensiveItems();

	UObject* OffensiveWeapon = TryGetOffensiveObject(Cast<UItem>(PrimaryWeapon));

	if (OffensiveWeapon)
	{
		OffensiveItems.Add(OffensiveWeapon);
	}

	OffensiveWeapon = TryGetOffensiveObject(Cast<UItem>(SecondaryWeapon));

	if (OffensiveWeapon)
	{
		OffensiveItems.Add(OffensiveWeapon);
	}
	
	return OffensiveItems;
}

UObject* UEquipment::TryGetOffensiveObject(UItem* Item)
{
	IOffensiveOption* OffensiveItem = Cast<IOffensiveOption>(Item);

	if (OffensiveItem)
	{
		return Cast<UObject>(OffensiveItem);
	}

	return nullptr;
}


