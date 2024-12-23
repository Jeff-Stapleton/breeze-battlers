// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Projectiles/XLProjectile.h"
#include "Characters/XLPlayerCharacter.h"
#include "Camera/XLCamera.h"
#include "Projectile/XLAbilityTargetProjectile.h"

AXLAbilityTargetProjectile::AXLAbilityTargetProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	ShouldProduceTargetDataOnServer = true;
	bDebug = true;
	bDestroyOnConfirmation = false;

	//FHitResult TargetingHitResult(ForceInit);
}

void AXLAbilityTargetProjectile::StartTargeting(UGameplayAbility * Ability)
{
	Super::StartTargeting(Ability);
	 
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();

	FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
	FVector Velocity = CalculateProjectileVelocity();
	SpawnProjectile(Origin, Velocity);
}

void AXLAbilityTargetProjectile::SpawnProjectile(FVector Origin, FVector Direction)
{
	FTransform SpawnTM(FVector::ZeroVector.Rotation(), Origin);
	AXLProjectile* Projectile = Cast<AXLProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileClass, SpawnTM));
	if (Projectile)
	{
		Projectile->InitVelocity(Direction);
		//Projectile->SetInstigator(SourceActor);
		Projectile->SetOwner(SourceActor);
		Projectile->CollisionComp->OnComponentHit.AddDynamic(this, &AXLAbilityTargetProjectile::OnHit);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}

void AXLAbilityTargetProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TargetingHitResult = Hit;
	//FGameplayAbilityTargetDataHandle Handle = MakeTargetData(Hit);
	//TargetDataReadyDelegate.Broadcast(Handle);
}

void AXLAbilityTargetProjectile::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		bDebug = false;
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(TargetingHitResult);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

FGameplayAbilityTargetDataHandle AXLAbilityTargetProjectile::MakeTargetData(const FHitResult& Hit) const
{
	if (OwningAbility)
	{
		/** Use the source location instead of the literal origin */
		return StartLocation.MakeTargetDataHandleFromHitResult(OwningAbility, Hit);
	}

	return FGameplayAbilityTargetDataHandle();
}

FVector AXLAbilityTargetProjectile::CalculateProjectileVelocity()
{
	AXLPlayerCharacter* Character = Cast<AXLPlayerCharacter>(SourceActor);
	AXLPlayerController* Controller = Cast<AXLPlayerController>(Character->GetController());

	FVector StartingLocation = StartLocation.GetTargetingTransform().GetLocation();
	FVector ForwardVector = Character->Camera->GetForwardVector();
	FVector TargetLocation = Trace(StartingLocation, StartingLocation + ForwardVector * 10000.0f);

	FVector AdjustedVector = (TargetLocation - StartingLocation).GetSafeNormal();
	return AdjustedVector;
}

FVector AXLAbilityTargetProjectile::Trace(FVector Origin, FVector Target)
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(PreTrace), true, SourceActor);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	SourceActor->GetWorld()->LineTraceSingleByChannel(Hit, Origin, Target, COLLISION_PROJECTILE, TraceParams);
	//Owner->GetWorld()->DebugDrawTraceTag = PreTraceTag;

	return Hit.bBlockingHit ? Hit.ImpactPoint : Hit.TraceEnd;
}