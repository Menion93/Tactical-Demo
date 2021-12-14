// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "BattleSystem/BattleManager.h"

UAction::UAction()
{

}

void UAction::Init_Implementation(ABattleManager* BM, AGCharacter* MyCharacter)
{
	Input = BM->Input;
	BattleManager = BM;
	Character = MyCharacter;
}


bool UAction::PlayAction_Implementation(float DeltaTime)
{
	return InputEventRAxis(DeltaTime) || 
		InputEventLAxis(DeltaTime) ||
		(Input->X_DOWN && InputEventX(DeltaTime)) ||
		(Input->Y_DOWN && InputEventY(DeltaTime)) ||
		(Input->A_DOWN && InputEventA(DeltaTime)) ||
		(Input->B_DOWN && InputEventB(DeltaTime)) ||
		(Input->Start_DOWN && InputEventStart(DeltaTime)) ||
		(Input->Pause_DOWN && InputEventPause(DeltaTime)) ||
		(Input->R1_DOWN && InputEventR1(DeltaTime)) ||
		(Input->R2_DOWN && InputEventR2(DeltaTime)) ||
		(Input->L1_DOWN && InputEventL1(DeltaTime)) ||
		(Input->L2_DOWN && InputEventL2(DeltaTime));
}

void UAction::OnEnter_Implementation()
{

}

void UAction::OnEnd_Implementation()
{

}


bool UAction::RevertAction_Implementation()
{
	Character->State->ActionPoints += ActionPoints;
	return false;
}


bool UAction::InputEventX_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventY_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventA_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventB_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventStart_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventPause_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventR1_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventR2_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventL1_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventL2_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventLAxis_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventRAxis_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventPadUpDown_Implementation(float DeltaTime)
{
	return false;
}

bool UAction::InputEventPadLeftRight_Implementation(float DeltaTime)
{
	return false;
}

