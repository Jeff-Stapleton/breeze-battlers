// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/XLItem.h"
#include "IOEquipmentSlot.h"
#include "IOEquipmentAttachment.h"
#include "IOGear.h"
#include "IOBelt.generated.h"

class AIOEquipment;

UCLASS()
class IO_API AIOBelt : public AIOGear
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	int32 Capacity;

	UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	void SelectEquipmentSlot(AIOEquipment* NewEquipment);

	UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	void OnRep_Equipment(TArray<AIOEquipment*> PreReplicationEquipment);
	
};
