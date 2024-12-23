// Fill out your copyright notice in the Description page of Project Settings.

#include "IOCharacterInputComponent.h"
#include "IOCharacter.h"
#include "Controllers/XLPlayerController.h"

void UIOCharacterInputComponent::Init(APlayerController* NewController)
{
	Super::Init(NewController);

	BindAction("EquipmentMenu", IE_Pressed, this, &UIOCharacterInputComponent::ShowEquipmentMenu);
	BindAction("EquipmentMenu", IE_Released, this, &UIOCharacterInputComponent::HideEquipmentMenu);
}

void UIOCharacterInputComponent::ShowEquipmentMenu()
{
	AIOCharacter* Character = Cast<AIOCharacter>(Controller->GetPawn());
	if (Character)
	{
		Character->ShowEquipmentMenu();
	}
}

void UIOCharacterInputComponent::HideEquipmentMenu()
{
	AIOCharacter* Character = Cast<AIOCharacter>(Controller->GetPawn());
	if (Character)
	{
		Character->HideEquipmentMenu();
	}
}
