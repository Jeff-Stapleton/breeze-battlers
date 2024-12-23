// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IOEquipment.h"
#include "Projectiles/XLProjectile.h"
#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Weapons/Components/Interfaces/XLTargetingComponent.h"
#include "Tactical.generated.h"

/**
 * 
 */
UCLASS()
class IO_API ATactical : public AIOEquipment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO | Tactical")
	TSubclassOf<UXLFireComponent> PrimaryActionComponentBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO | Tactical")
	TSubclassOf<UXLTargetingComponent> SecondaryActionComponentBP;

	UPROPERTY(BlueprintReadWrite, Category = "IO | Tactical")
	UXLFireComponent* PrimaryActionComponent;

	UPROPERTY(BlueprintReadWrite, Category = "IO | Tactical")
	UXLTargetingComponent* SecondaryActionComponent;

	ATactical();

	virtual void BeginPlay() override;

};
