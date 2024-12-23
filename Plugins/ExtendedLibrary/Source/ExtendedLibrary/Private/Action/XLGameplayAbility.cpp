// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Projectiles/XLProjectile.h"
#include "Action/XLGameplayAbility.h"

UXLGameplayAbility::UXLGameplayAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UXLGameplayAbility::SpawnProjectile(TSubclassOf<AXLProjectile> ProjectileClass, FVector Origin, FVector Direction, TArray<TSubclassOf<UXLGameplayEffect>> TargetGameplayEffects)
{
	FTransform SpawnTM(FVector::ZeroVector.Rotation(), Origin);
	AXLProjectile* Projectile = Cast<AXLProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetAvatarActorFromActorInfo(), ProjectileClass, SpawnTM));
	if (Projectile)
	{
		//Projectile->SetOwner(this);
		//Projectile->SetInstigator(this);
		Projectile->TargetGameplayEffects = TargetGameplayEffects;
		Projectile->InitVelocity(Direction);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}