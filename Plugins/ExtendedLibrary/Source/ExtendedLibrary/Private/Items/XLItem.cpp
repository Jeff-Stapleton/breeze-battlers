
// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Structs/XLItemAnimations.h"
#include "Structs/XLItemSounds.h"
#include "Items/XLItem.h"

AXLItem::AXLItem()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(true);
	Mesh1P->SetReceivesDecals(false);
	Mesh1P->SetCastShadow(false);
	Mesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh1P->SetupAttachment(Root);
	Mesh1P->SetVisibility(false);

	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh3P"));
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh3P->SetReceivesDecals(false);
	Mesh3P->SetCastShadow(true);
	Mesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	Mesh3P->SetupAttachment(Root);
	Mesh3P->SetVisibility(false);
	//NetCullDistanceSquared = 255000000.0;
	//bNetUseOwnerRelevancy = false;

	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void AXLItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AXLItem::Destroyed()
{
	Super::Destroyed();
}

void AXLItem::SetOwningPawn(AXLCharacter* NewOwner)
{
	if (Character != NewOwner)
	{
		SetInstigator(NewOwner);
		Character = NewOwner;
		Character->DeathDelegate.AddDynamic(this, &AXLItem::OnCharacterDeath);
		// net owner for RPC calls
		SetOwner(NewOwner);
	}
}

void AXLItem::OnRep_MyPawn()
{
	if (Character)
	{
		SetOwningPawn(Character);
	}
	else
	{
		Remove();
	}
}

void AXLItem::Remove()
{
	Detach();

	if (GetLocalRole() == ROLE_Authority)
	{
		SetOwningPawn(NULL);
	}
}

void AXLItem::OnCharacterDeath()
{
 	CharacterDeathDelegate.Broadcast();
}

void AXLItem::TogglePerspective()
{
	class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);

	if (MyPC && MyPC->IsFirstPerson)
	{
		Mesh1P->SetOwnerNoSee(false);
		Mesh3P->SetOwnerNoSee(true);
	}
	else
	{
		Mesh1P->SetOwnerNoSee(true);
		Mesh3P->SetOwnerNoSee(false);
	}
}

void AXLItem::HandlePlayFX_Implementation(UParticleSystem* FX, FName AttachPoint)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		UParticleSystemComponent* FXComponent = NULL;
		if (FX)
		{
			FXComponent = UGameplayStatics::SpawnEmitterAttached(FX, Mesh3P, AttachPoint);
		}
	}
}
bool AXLItem::PlayFX_Validate(UParticleSystem* FX, FName AttachPoint)
{
	return true;
}
void AXLItem::PlayFX_Implementation(UParticleSystem* FX, FName AttachPoint)
{
	HandlePlayFX(FX, AttachPoint);
}

void AXLItem::HandlePlaySound_Implementation(USoundCue* Sound)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		UAudioComponent* AC = NULL;
		if (Sound && Character)
		{
			AC = UGameplayStatics::SpawnSoundAttached(Sound, Character->GetRootComponent());
		}
	}
}
bool AXLItem::PlaySound_Validate(USoundCue* Sound)
{
	return true;
}
void AXLItem::PlaySound_Implementation(USoundCue* Sound)
{
	HandlePlaySound(Sound);
}

void AXLItem::HandlePlayAnimation_Implementation(class UAnimMontage* Animation, float InPlayRate)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		//USkeletalMeshComponent* UseMesh = GetMesh();
		if (Animation && Mesh3P && Mesh3P->AnimScriptInstance)
		{
			Mesh3P->AnimScriptInstance->Montage_Play(Animation, InPlayRate);
		}
	}
}
bool AXLItem::PlayAnimation_Validate(class UAnimMontage* Animation, float InPlayRate)
{
	return true;
}
void AXLItem::PlayAnimation_Implementation(class UAnimMontage* Animation, float InPlayRate)
{
	HandlePlayAnimation(Animation, InPlayRate);
}

FVector AXLItem::GetSocketLocation(FName SocketName)
{
	if (Character && Character->IsLocallyControlled())
	{
		class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);
		if (MyPC && MyPC->IsFirstPerson)
		{
			if (Mesh1P->DoesSocketExist(SocketName))
			{
				return Mesh1P->GetSocketLocation(SocketName);
			}
			if (Character->Head->DoesSocketExist(SocketName))
			{
				return Character->Head->GetSocketLocation(SocketName);
			}
		}
		else
		{
			if (Mesh3P->DoesSocketExist(SocketName))
			{
				return Mesh3P->GetSocketLocation(SocketName);
			}
			if (Character->Head->DoesSocketExist(SocketName))
			{
				return Character->Head->GetSocketLocation(SocketName);
			}
		}
	}
	return FVector::ZeroVector;
}

void AXLItem::Attach(USkeletalMeshComponent* AttachMesh3P, FName AttachPoint)
{
	AttachToComponent(AttachMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	//AttachToActor(Character, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	//if (Tags.Contains("equipable") && Character)
	//{
	//	Detach();
	//	if (Character->IsLocallyControlled())
	//	{
	//		//AttachToComponent(AttachMesh3P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
	//		Mesh1P->AttachToComponent(AttachMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	//		Mesh3P->AttachToComponent(AttachMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);

	//		TogglePerspective();
	//	}
	//	else
	//	{
	//		//AttachToComponent(AttachMesh3P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
	//		Mesh1P->AttachToComponent(AttachMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	//		Mesh3P->AttachToComponent(AttachMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	//	}
	//	//AttachToActor(Character, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
	//}
}

void AXLItem::SetVisibility(bool Visibility, bool Include1PMesh)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ServerSetVisibility(Visibility, Include1PMesh);
	}
}

void AXLItem::ServerSetVisibility_Implementation(bool Visibility, bool Include1PMesh)
{
	Mesh3P->SetVisibility(Visibility);
	if (Include1PMesh)
	{
		Mesh1P->SetVisibility(Visibility);
	}
}



void AXLItem::Detach()
{
	//DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh3P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh1P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}

void AXLItem::Equip()
{
	//if (Count > 0)
	//{
		//Mesh3P->SetVisibility(true);
	//}
}

void AXLItem::Unequip()
{
	Mesh3P->SetVisibility(false);
}

void AXLItem::Drop()
{
	this->Destroy();
}

void AXLItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AXLItem, Character);
	DOREPLIFETIME(AXLItem, Socket);
	DOREPLIFETIME(AXLItem, StowedMesh3P);
	DOREPLIFETIME(AXLItem, StowedMesh1P);
}
