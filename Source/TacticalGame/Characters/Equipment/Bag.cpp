// Fill out your copyright notice in the Description page of Project Settings.


#include "Bag.h"
#include "Interfaces/OffensiveOption.h"

// Sets default values for this component's properties
UBag::UBag()
{

}

TArray<UItem*> UBag::GetItems()
{
	TArray<UItem*> Result;

	return Result;
}

TArray<UObject*> UBag::GetOffensiveItems()
{
	TArray<UObject*> OffensiveItems;

	for (auto& Item : Items)
	{
		IOffensiveOption* OffensiveItem = Cast<IOffensiveOption>(Item);

		if (OffensiveItem)
		{
			OffensiveItems.Add(Cast<UObject>(OffensiveItem));
		}
	}

	return OffensiveItems;
}
