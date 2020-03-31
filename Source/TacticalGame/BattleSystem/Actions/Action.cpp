// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "BattleSystem/BattleManager.h"

UAction::UAction()
{

}

void UAction::Init_Implementation(ABattleManager* BM)
{
	Input = BM->Input;
	BattleManager = BM;
}


bool UAction::PlayAction_Implementation()
{
	return (Input->X_DOWN && InputEventX()) ||
		(Input->Y_DOWN && InputEventY()) ||
		(Input->A_DOWN && InputEventA()) ||
		(Input->B_DOWN && InputEventB()) ||
		(Input->Start_DOWN && InputEventStart()) ||
		(Input->Pause_DOWN && InputEventPause()) ||
		(Input->R1_DOWN & InputEventR1()) ||
		(Input->R2_DOWN && InputEventR2()) ||
		(Input->L1_DOWN && InputEventL1()) ||
		(Input->L2_DOWN && InputEventL2()) ||
		InputEventLAxis();
}

void UAction::OnEnter_Implementation()
{

}

void UAction::OnEnd_Implementation()
{

}


bool UAction::RevertAction_Implementation()
{
	return false;
}


bool UAction::CanExecuteAction_Implementation() 
{
	return false;
}

bool UAction::InputEventX_Implementation()
{
	return false;
}

bool UAction::InputEventY_Implementation()
{
	return false;
}

bool UAction::InputEventA_Implementation()
{
	return false;
}

bool UAction::InputEventB_Implementation()
{
	return false;
}

bool UAction::InputEventStart_Implementation()
{
	return false;
}

bool UAction::InputEventPause_Implementation()
{
	return false;
}

bool UAction::InputEventR1_Implementation()
{
	return false;
}

bool UAction::InputEventR2_Implementation()
{
	return false;
}

bool UAction::InputEventL1_Implementation()
{
	return false;
}

bool UAction::InputEventL2_Implementation()
{
	return false;
}

bool UAction::InputEventLAxis_Implementation()
{
	return false;
}

bool UAction::InputEventRAxis_Implementation()
{
	return false;
}

bool UAction::InputEventPadUpDown_Implementation()
{
	return false;
}

bool UAction::InputEventPadLeftRight_Implementation()
{
	return false;
}

