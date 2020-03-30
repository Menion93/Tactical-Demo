// Fill out your copyright notice in the Description page of Project Settings.


#include "BSMState.h"
#include "BattleSystem/PlayerFireTeam.h"
#include "Globals/TacticalGameMode.h"


UBSMState::UBSMState() {}

void UBSMState::Init(APlayerFireTeam* SM)
{
	ATacticalGameMode* GameMode = Cast<ATacticalGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		Grid = GameMode->Grid;
	}

	Input = Cast<AGPlayerController>(GetWorld()->GetFirstPlayerController());

	BattleManager = GameMode->BattleManager;

	StateMachine = SM;

}

void UBSMState::PlayState()
{
	(Input->X_DOWN && InputEventX()) ||
	(Input->Y_DOWN && InputEventY()) ||
	(Input->A_DOWN && InputEventA()) ||
	(Input->B_DOWN && InputEventB()) ||
	(Input->Start_DOWN && InputEventStart()) ||
	(Input->Pause_DOWN && InputEventPause()) ||
	(Input->R1_DOWN && InputEventR1()) ||
	(Input->R2_DOWN && InputEventR2()) ||
	(Input->L1_DOWN && InputEventL1()) ||
	(Input->L2_DOWN && InputEventL2()) ||
	InputEventLAxis();
}

void UBSMState::BindState()
{

}

void UBSMState::UnbindState()
{

}

bool UBSMState::IsInputDisabled()
{
	return InputDisabled;
}

void UBSMState::DisableInput(bool DisInput)
{
	InputDisabled = DisInput;
}

bool UBSMState::InputEventX()
{
	return false;
}

bool UBSMState::InputEventY()
{
	return false;
}

bool UBSMState::InputEventA()
{
	return false;
}

bool UBSMState::InputEventB()
{
	return false;
}

bool UBSMState::InputEventStart()
{
	return false;
}

bool UBSMState::InputEventPause()
{
	return false;
}

bool UBSMState::InputEventR1()
{
	return false;
}

bool UBSMState::InputEventR2()
{
	return false;
}

bool UBSMState::InputEventL1()
{
	return false;
}

bool UBSMState::InputEventL2()
{
	return false;
}

bool UBSMState::InputEventLAxis()
{
	return false;
}

bool UBSMState::InputEventRAxis()
{
	return false;
}

bool UBSMState::InputEventPadUpDown()
{
	return false;
}

bool UBSMState::InputEventPadLeftRight()
{
	return false;
}

void UBSMState::OnEnter()
{

}



