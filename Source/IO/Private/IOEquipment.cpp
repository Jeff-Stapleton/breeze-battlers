// Fill out your copyright notice in the Description page of Project Settings.

#include "IOEquipment.h"

#include "Net/UnrealNetwork.h"
#include "IOEquipmentAttachment.h"
#include "Characters/XLCharacter.h"
#include "IO.h"

AIOEquipment::AIOEquipment()
{
	bReplicates = true;
}

void AIOEquipment::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		for (int32 i = 0; i < DefaultAttachments.Num(); i++)
		{
			if (DefaultAttachments[i])
			{
				AIOEquipmentAttachment* NewAttachment = GetWorld()->SpawnActor<AIOEquipmentAttachment>(DefaultAttachments[i], SpawnInfo);
				int32 index = CurrentCapacity + NewAttachment->Capacity / 2;
				CurrentCapacity += NewAttachment->Capacity;
				Attachments.Add(NewAttachment);
				NewAttachment->AttachToComponent(Mesh3P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Sockets[index]);
			}
		}
	}
}

void AIOEquipment::Slot(UStaticMeshComponent* Attachee, FName Socket)
{
	Attachee->AttachToComponent(Mesh3P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
}

void AIOEquipment::Equip_Implementation()
{
	Super::Equip();

	if (HideAttachmentOnEquip)
	{
		if (AttachedMeshes.IsValidIndex(AttachedMeshIndex))
		{
			AttachedMeshes[AttachedMeshIndex]->Mesh->SetVisibility(false);
		}
	}
	if (AnimClass)
	{
		Character->Head->SetAnimInstanceClass(AnimClass);
	}
}
bool AIOEquipment::ServerEquip_Validate()
{
	return true;
}
void AIOEquipment::ServerEquip_Implementation()
{
	Equip();
}

void AIOEquipment::Unequip_Implementation()
{
	Super::Unequip();

	if (HideAttachmentOnEquip)
	{
		if (AttachedMeshes.IsValidIndex(AttachedMeshIndex))
		{
			AttachedMeshes[AttachedMeshIndex]->Mesh->SetVisibility(true);
		}
	}
}
bool AIOEquipment::ServerUnequip_Validate()
{
	return true;
}
void AIOEquipment::ServerUnequip_Implementation()
{
	Unequip();
}

void AIOEquipment::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIOEquipment, CurrentCapacity);
	DOREPLIFETIME(AIOEquipment, AttachedMeshes);
	DOREPLIFETIME(AIOEquipment, Attachments);
}