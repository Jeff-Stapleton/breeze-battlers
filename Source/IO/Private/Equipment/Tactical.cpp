// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/Tactical.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "Characters/XLCharacter.h"
#include "IOCharacter.h"

ATactical::ATactical()
{
	bReplicates = true;
}

void ATactical::BeginPlay()
{
	Super::BeginPlay();
}

