// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Interfaces/OffensiveOption.h"

UEquipment::UEquipment()
{

}

void UEquipment::LoadDefaultEquipment()
{
	UPROPERTY(EditAnywere, BlueprintReadWrite)
	PrimaryWeapon = NewObject<UWeaponCore>(this, PrimaryWeaponClass);

	UPROPERTY(EditAnywere, BlueprintReadWrite)
	SecondaryWeapon = NewObject<UWeaponCore>(this, SecondaryWeaponClass);

	UPROPERTY(EditAnywere, BlueprintReadWrite);
	Bag = NewObject<UBag>(this, BagClass);

	UPROPERTY(EditAnywere, BlueprintReadWrite);
	Armor = NewObject<UArmor>(this, ArmorClass);

	UPROPERTY(EditAnywere, BlueprintReadWrite);
	Shield = NewObject<UShield>(this, ShieldClass);
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
	IOffensiveOption* OffensiveItem = Cast<IOffensiveOption>(SecondaryWeapon);

	if (OffensiveItem)
	{
		return Cast<UObject>(OffensiveItem);
	}

	return nullptr;
}


