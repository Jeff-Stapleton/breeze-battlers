#pragma once

#include "IOEquipmentSlotType.h"
#include "IOEquipmentSlot.generated.h"

class AIOEquipment;

USTRUCT(BlueprintType)
struct FEquipmentSlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TEnumAsByte<EEquipmentSlotType::Type> EquipmentSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	FName Socket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	bool IsEmpty;

	UPROPERTY(BlueprintReadWrite, Category = "IO|Equipment")
	AIOEquipment* Equipment;
};