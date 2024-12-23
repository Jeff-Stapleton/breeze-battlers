#pragma once

#include "IOEquipmentSlotType.h"
#include "IOEquipmentAttachmentType.h"
#include "IOEquipmentAttachment.generated.h"

class AIOEquipment;
class AIOAttachedEquipment;

UCLASS()
class IO_API AIOEquipmentAttachment : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TEnumAsByte<EEquipmentSlotType::Type> EquipmentSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TEnumAsByte<EIOEquipmentAttachmentType::Type> EquipmentAttachmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	int32 Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	int32 StorageCapacity;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "IO|Equipment")
	int32 CurrentStorage;

	UPROPERTY(BlueprintReadWrite, Category = "IO|Equipment")
	AIOEquipment* Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	int32 SocketIndex;

public:

	AIOEquipmentAttachment();

	void Slot(AIOAttachedEquipment* Slotable);

};