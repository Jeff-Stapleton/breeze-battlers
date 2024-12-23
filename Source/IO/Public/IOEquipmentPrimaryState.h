#pragma once

UENUM(BlueprintType, Category = "IO|Enums")
namespace EEquipmentPrimaryState
{
	enum Type
	{
		Idle,
		Activated,
		Reloading,
		Meleeing,
		OutOfAmmo,
		NotReady
	};
}