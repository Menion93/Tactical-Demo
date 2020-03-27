// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "BattleSystem/BattleManager.h"

UAction::UAction()
{

}

void UAction::Init(ABattleManager* BM)
{
	Input = BM->Input;
	BattleManager = BM;
}

bool UAction::PlayAction_Implementation()
{
	if (Input->X_DOWN)
	{
		InputEventX_Implementation();
	}

	if (Input->Y_DOWN)
	{
		InputEventY_Implementation();
	}

	if (Input->A_DOWN)
	{
		InputEventA_Implementation();
	}

	if (Input->B_DOWN)
	{
		InputEventB_Implementation();
	}

	if (Input->Start_DOWN)
	{
		InputEventStart_Implementation();
	}

	if (Input->Pause_DOWN)
	{
		InputEventPause_Implementation();
	}

	if (Input->R1_DOWN)
	{
		InputEventR1_Implementation();
	}

	InputEventLAxis_Implementation();

	return false;
}

void UAction::OnEnter_Implementation()
{

}

void UAction::OnEnd_Implementation()
{

}


void UAction::ReverseAction_Implementation()
{

}


bool UAction::CanExecuteAction_Implementation() 
{
	return false;
}

void UAction::InputEventX_Implementation()
{

}

void UAction::InputEventY_Implementation()
{

}

void UAction::InputEventA_Implementation()
{

}

void UAction::InputEventB_Implementation()
{

}

void UAction::InputEventStart_Implementation()
{

}

void UAction::InputEventPause_Implementation()
{

}

void UAction::InputEventR1_Implementation()
{

}

void UAction::InputEventR2_Implementation()
{

}

void UAction::InputEventL1_Implementation()
{

}

void UAction::InputEventL2_Implementation()
{

}

void UAction::InputEventLAxis_Implementation()
{

}

void UAction::InputEventRAxis_Implementation()
{

}

void UAction::InputEventPadUpDown_Implementation()
{

}

void UAction::InputEventPadLeftRight_Implementation()
{

}

