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

void UBSMState::PlayState(float DeltaTime)
{
	InputEventRAxis(DeltaTime) ||
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


bool UBSMState::IsInputDisabled()
{
	return InputDisabled;
}

void UBSMState::DisableInput(bool DisInput)
{
	InputDisabled = DisInput;
}

bool UBSMState::InputEventX(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventY(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventA(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventB(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventStart(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventPause(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventR1(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventR2(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventL1(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventL2(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventLAxis(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventRAxis(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventPadUpDown(float DeltaTime)
{
	return false;
}

bool UBSMState::InputEventPadLeftRight(float DeltaTime)
{
	return false;
}

void UBSMState::OnEnter()
{

}



