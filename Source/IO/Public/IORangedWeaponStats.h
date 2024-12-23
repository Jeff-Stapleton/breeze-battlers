#pragma once

#include "IORangedWeaponStats.generated.h"

//class AIOEquipment;

USTRUCT(BlueprintType)
struct FIORangedWeaponStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Weapon")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IO|Weapon")
	int32 Capacity;
};