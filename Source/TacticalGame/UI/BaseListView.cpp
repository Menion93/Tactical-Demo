// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseListView.h"
#include "Globals/TacticalGameMode.h"


void UBaseListView::Init(TArray<UObject*> Entries, UListView* LV)
{
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());
	Input = GameMode->Input;

	ListView = LV;
	ListView->SetListItems(Entries);

	Index = 0;
	if (ListView->GetNumItems() > 0)
	{
		ListView->SetSelectedIndex(Index);
	}
}

void UBaseListView::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);

	AxisInput();
	AInput();
}

void UBaseListView::AxisInput_Implementation()
{
	if (Input && Input->LAxis_DOWN)
	{
		if (Input->LAxis.X > 0)
		{
			Index = FMath::Max(--Index, 0);
		}
		else
		{
			Index = FMath::Min(++Index, ListView->GetNumItems() - 1);
		}

		ListView->SetSelectedIndex(Index);
	}
}

void UBaseListView::AInput_Implementation()
{

}