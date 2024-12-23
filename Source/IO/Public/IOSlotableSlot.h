#pragma once

#include "IOSlotableSlotType.h"
#include "IOSlotableSlot.generated.h"

class AIOEquipment;

USTRUCT(BlueprintType)
struct FSlotableSlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TEnumAsByte<ESlotableSlotType::Type> SlotableSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	FName Socket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	bool IsEmpty;

	UPROPERTY(BlueprintReadWrite, Category = "IO|Equipment")
	AIOEquipment* Equipment;
};