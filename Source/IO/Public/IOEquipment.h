// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/XLItem.h"
#include "IOEquipmentSlotType.h"
#include "IOEquipmentSlot.h"
#include "IOEquipmentAttachment.h"
#include "IOEquipmentPrimaryState.h"
#include "IOAttachedEquipment.h"
#include "IOEquipmentSecondaryState.h"
#include "IOEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentPrimaryStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentSecondaryStateDelegate);

UCLASS()
class IO_API AIOEquipment : public AXLItem
{
	GENERATED_BODY()
	
public: 				
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	bool IsShownInInventoryWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TEnumAsByte<EEquipmentSlotType::Type> EquipmentSlotType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<FEquipmentSlot> AdditionalSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<TSubclassOf<AIOEquipmentAttachment>> DefaultAttachments;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<AIOEquipmentAttachment*> Attachments;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<FName> Sockets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	bool UsesAttachedMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Equipment")
	TSubclassOf<AIOAttachedEquipment>AttachedMeshTemplate;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Equipment")
	TArray<AIOAttachedEquipment*> AttachedMeshes;

	int32 AttachedMeshIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	int32 MaxCapacity;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "IO|Equipment")
	int32 CurrentCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	bool DestoryAttachmentOnUse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	bool HideAttachmentOnEquip;

public:

	AIOEquipment();

	virtual void BeginPlay() override;

	void Slot(UStaticMeshComponent* Attachee, FName Socket);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "XL|Item")
	virtual void Equip() override;
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable)
	virtual void ServerEquip();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "XL|Item")
	virtual void Unequip() override;
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable)
	virtual void ServerUnequip();

};
