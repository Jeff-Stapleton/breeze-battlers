// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IOEquipment.h"
#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "IOHealthPack.generated.h"

/**
 * 
 */
UCLASS()
class IO_API AIOHealthPack : public AIOEquipment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO | Consumable")
	TSubclassOf<UXLFireComponent> PrimaryActionComponentBP;

	UPROPERTY(BlueprintReadWrite, Category = "IO | Consumable")
	UXLFireComponent* PrimaryActionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Consumable")
	float ChargeTime = 3.0f;
	UPROPERTY(BlueprintReadWrite, Category = "XL | Consumable")
	float CurrentCharge = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Consumable")
	float MaxUses = 5.0f;
	UPROPERTY(BlueprintReadWrite, Category = "XL | Consumable")
	float RemainingUses = 0.0f;

	FTimerHandle ChargeTimer;

	AIOHealthPack();

	virtual void BeginPlay() override;

	void Heal();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerHeal();

};
