// Fill out your copyright notice in the Description page of Project Settings.


#include "Bag.h"
#include "BattleSystem/Actions/Actionable.h"


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
		IActionable* ActionableItem = Cast<IActionable>(Item);

		if (ActionableItem->Execute_GetActionType(Item) == ActionType::OFFENSIVE)
		{
			OffensiveItems.Add(Cast<UObject>(ActionableItem));
		}
	}

	return OffensiveItems;
}

TArray<UObject*> UBag::GetSupportItems()
{
	TArray<UObject*> SupportItems;

	for (auto& Item : Items)
	{
		IActionable* ActionableItem = Cast<IActionable>(Item);

		if (ActionableItem->Execute_GetActionType(Item) == ActionType::SUPPORT)
		{
			SupportItems.Add(Cast<UObject>(ActionableItem));
		}
	}

	return SupportItems;
}