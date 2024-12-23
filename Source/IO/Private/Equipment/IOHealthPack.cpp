// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/IOHealthPack.h"
#include "Characters/XLCharacter.h"
#include "Data/Character/XLCharacterResources.h"
#include "IOCharacter.h"

AIOHealthPack::AIOHealthPack()
{
	bReplicates = true;
}

void AIOHealthPack::BeginPlay()
{
	Super::BeginPlay();

	RemainingUses = MaxUses;
}

void AIOHealthPack::Heal()
{
	ServerHeal();
	RemainingUses--;
}

bool AIOHealthPack::ServerHeal_Validate()
{
	return true;
}

void AIOHealthPack::ServerHeal_Implementation()
{
	Character->CharacterResources->CurrentHealth = Character->CharacterResources->MaxHealth;
}
