// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "AbilitySystemComponent.h"
#include "Data/XLCharacterAttributeSet.h"
#include "Calculations/XLTakeDamageExecutionCalculation.h"

struct XLDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	XLDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UXLCharacterAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UXLCharacterAttributeSet, Damage, Source, false);
	}
};

static const XLDamageStatics& DamageStatics()
{
	static XLDamageStatics DStatics;
	return DStatics;
}

UXLTakeDamageExecutionCalculation::UXLTakeDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UXLTakeDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput &OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystem = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystem = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystem ? TargetAbilitySystem->GetAvatarActor() : nullptr;
	AActor* SourceActor = SourceAbilitySystem ? SourceAbilitySystem->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec &Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float CurrentHealth = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, CurrentHealth);

	float BaseDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, BaseDamage);

	BaseDamage *= -1.0f;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, BaseDamage));
}