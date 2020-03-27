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
	if (Input->X_DOWN)
	{
		InputEventX();
	}

	if (Input->Y_DOWN)
	{
		InputEventY();
	}

	if (Input->A_DOWN)
	{
		InputEventA();
	}

	if (Input->B_DOWN)
	{
		InputEventB();
	}

	if (Input->Start_DOWN)
	{
		InputEventStart();
	}

	if (Input->Pause_DOWN)
	{
		InputEventPause();
	}

	if (Input->R1_DOWN)
	{
		InputEventR1();
	}

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

void UBSMState::InputEventX()
{

}

void UBSMState::InputEventY()
{

}

void UBSMState::InputEventA()
{

}

void UBSMState::InputEventB()
{

}

void UBSMState::InputEventStart()
{

}

void UBSMState::InputEventPause()
{

}

void UBSMState::InputEventR1()
{

}

void UBSMState::InputEventR2()
{

}

void UBSMState::InputEventL1()
{

}

void UBSMState::InputEventL2()
{

}

void UBSMState::InputEventLAxis()
{

}

void UBSMState::InputEventRAxis()
{

}

void UBSMState::InputEventPadUpDown()
{

}

void UBSMState::InputEventPadLeftRight()
{

}

void UBSMState::OnEnter()
{

}



