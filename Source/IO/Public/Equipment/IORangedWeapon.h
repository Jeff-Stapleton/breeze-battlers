// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IOEquipment.h"
#include "IORangedWeaponStats.h"
#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Weapons/Components/Interfaces/XLTargetingComponent.h"
#include "IORangedWeapon.generated.h"

class UXLFireComponent;
class UXLTargetingComponent;

UCLASS()
class IO_API AIORangedWeapon : public AIOEquipment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "IO|Equipment")
	FIORangedWeaponStats WeaponStats;

public:

	AIORangedWeapon();
	
	virtual void BeginPlay() override;

};
