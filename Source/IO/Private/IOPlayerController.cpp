// Fill out your copyright notice in the Description page of Project Settings.

#include "IOPlayerController.h"
#include "Engine/InputDelegateBinding.h"
#include "IOCharacterInputComponent.h"

AIOPlayerController::AIOPlayerController()
{
}

void AIOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	ResetInputMode();

	IOCharacterInputComponent = NewObject<UIOCharacterInputComponent>(this);
	IOCharacterInputComponent->Init(this);

	if (UInputDelegateBinding::SupportsInputDelegate(GetClass()))
	{
		UInputDelegateBinding::BindInputDelegates(GetClass(), IOCharacterInputComponent);
	}

	SetControllerInputMode(InputMode);
}

void AIOPlayerController::SetControllerInputMode(TEnumAsByte<EInputMode::Type> Mode)
{
	ResetInputMode();
	switch (Mode)
	{
	case EInputMode::Character:
		PushInputComponent(IOCharacterInputComponent);
		break;
	default:
		PushInputComponent(IOCharacterInputComponent);
		break;
	}
}