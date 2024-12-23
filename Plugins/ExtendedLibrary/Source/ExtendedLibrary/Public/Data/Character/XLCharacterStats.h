#pragma once

#include "Components/ActorComponent.h"
#include "XLCharacterStats.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLCharacterStats();

	/** The amount of health restored per second */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HealthRegen;

	/** The amount of energy restored per second */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float EnergyRegen;

	/** The amount of stamina restored per second */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float StaminaRegen;

	/** The amount of stamina restored per second */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float ShieldRegen;

	/** The time between consecutive attacks */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float AttackSpeed;

	/** The amount of damage a basic attack deals */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float AttackPower;

	/** The percentage of time all ability cooldowns are reduced */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float CooldownReduction;

	/** The precentage of damage all abilities are increased */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float AbilityPower;

	/** The precentage of damage reduced from physical attacks */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float PhysicalDefense;

	/** The precentage of damage reduced from energy attacks */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Stats)
	float EnergyDefense;
};