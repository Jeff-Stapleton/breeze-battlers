// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "XLTakeDamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDLIBRARY_API UXLTakeDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UXLTakeDamageExecutionCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput &OutExecutionOutput) const override;

};
