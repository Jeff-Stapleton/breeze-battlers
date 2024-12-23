#pragma once

#include "GameFramework/Actor.h"
#include "Structs/XLProjectileData.h"
#include "XLProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class AXLImpactFX;
class UXLGameplayEffect;
class UAudioComponent;
class UParticleSystemComponent;

UCLASS(Abstract, Blueprintable)
class EXTENDEDLIBRARY_API AXLProjectile : public AActor
{
	GENERATED_BODY()

	AXLProjectile(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "XL | Projectile")
	FXLProjectileData ProjectileData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XL | Projectile")
	TArray<TSubclassOf<UXLGameplayEffect>> TargetGameplayEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Projectile")
	float DetonationTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Projectile")
	bool IsTactical = false;

	UPROPERTY(EditDefaultsOnly, Category = "XL | Projectile")
	TSubclassOf<AXLImpactFX> ImpactFX;

	UPROPERTY(VisibleDefaultsOnly, Category = "XL | Projectile")
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "XL | Projectile")
	UParticleSystemComponent* TrailFX;

	UPROPERTY(VisibleDefaultsOnly, Category = "XL | Projectile")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, Transient)
	UAudioComponent* AudioComp;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_Impact)
	bool bImpact;

	FTimerHandle DetonationTimer;

public:

	void InitVelocity(FVector& ShootDirection);

	UFUNCTION()
	void OnImpact(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:

	UFUNCTION()
	void OnRep_Impact();

	void Explode();

	void Hit(const FHitResult& HitResult);

	void Impact(const FHitResult& HitResult);

	void ApplyGameplayEffects(TArray<AXLCharacter*> Targets);

	void Explosion();

	void DisableAndDestroy();
};
