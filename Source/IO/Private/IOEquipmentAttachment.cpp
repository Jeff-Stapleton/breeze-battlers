// Fill out your copyright notice in the Description page of Project Settings.


#include "IOEquipmentAttachment.h"
#include "Net/UnrealNetwork.h"
#include "IOAttachedEquipment.h"

// Sets default values

AIOEquipmentAttachment::AIOEquipmentAttachment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AttachmentMesh"));
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh->SetReceivesDecals(false);
	Mesh->SetCastShadow(true);
	Mesh->SetCollisionObjectType(ECC_WorldStatic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetupAttachment(Root);

	bReplicates = true;
}

void AIOEquipmentAttachment::Slot(AIOAttachedEquipment* Slotable)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Slotable->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Slot01");
}

void AIOEquipmentAttachment::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIOEquipmentAttachment, CurrentStorage);
}

