// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMenuItem.h"

void UBattleMenuItem::Init(ABattleManager* BM)
{
	BattleManager = BM;
}

bool UBattleMenuItem::ShowMenuOption_Implementation()
{
	return false;
}


void UBattleMenuItem::OnOptionSelected_Implementation()
{

}
