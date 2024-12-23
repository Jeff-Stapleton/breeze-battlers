// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "XLAbilityTargetProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;
class UParticleSystemComponent;
class AXLProjectile;

UCLASS()
class EXTENDEDLIBRARY_API AXLAbilityTargetProjectile : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
	AXLAbilityTargetProjectile(const FObjectInitializer& ObjectInitializer);

public: 

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AXLProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Projectile")
	float ProjectileSpeed;

	UPROPERTY(VisibleDefaultsOnly, Category = "XL | Projectile")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "XL | Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "XL | Projectile")
	UParticleSystemComponent* ParticleSystemComponent;

	FHitResult TargetingHitResult;

public:

	virtual void StartTargeting(UGameplayAbility * Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SpawnProjectile(FVector Origin, FVector Direction);

	FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& Hit) const;

protected:

	virtual FVector CalculateProjectileVelocity();

	FVector Trace(FVector Origin, FVector Target);

};
