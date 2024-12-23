// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Characters/XLPlayerCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "IOEquipmentSlot.h"
#include "IOEquipmentAttachment.h"
#include "IOCharacter.generated.h"

class UInputComponent;
class AXLPickup;
class UUserWidget;
class AIOEquipment;
class AIOGear;

UCLASS(config=Game)
class AIOCharacter : public AXLPlayerCharacter
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditDefaultsOnly, Category = "IO|UI")
	TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "IO|UI")
	TSubclassOf<UUserWidget> EquipmentWidget;
	UPROPERTY()
	UUserWidget* EquipmentWheel;

	UPROPERTY(BlueprintReadWrite, Category = "IO|UI")
	bool IsInventoryOpen = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<FEquipmentSlot> WearableSlots;

	UPROPERTY(EditDefaultsOnly, Category = "IO|Equipment")
	TArray<TSubclassOf<AIOEquipment>> DefaultWearables;

	UPROPERTY(ReplicatedUsing = OnRep_Wearables, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<AIOEquipment*> Wearables;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<AIOEquipmentAttachment*> Mods;

	UPROPERTY(EditDefaultsOnly, Category = "IO|Equipment")
	TSubclassOf<AIOEquipment> UnarmedBP;
	UPROPERTY(BlueprintReadWrite, Category = "IO|Equipment")
	AIOEquipment* Unarmed;

	UPROPERTY(EditDefaultsOnly, Category = "IO|Equipment")
	TArray<TSubclassOf<AIOEquipment>> DefaultSlotables;

	UPROPERTY(ReplicatedUsing = OnRep_Slotables, BlueprintReadWrite, Category = "IO|Equipment")
	TArray<AIOEquipment*> Slotables;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "IO|Currency")
	int32 Coins;

	UPROPERTY(EditDefaultsOnly, Category = "IO|Currency")
	TSubclassOf<AXLPickup> PickupClass;

	AIOCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	void SpawnInventory();

	bool EquipmentContains(FName id);
	AIOEquipment* EquipmentFind(FName id);


	//UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	//void SpawnGear();

	//UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	//void Equip(AIOGear* Item);

	//UFUNCTION(Reliable, Server, WithValidation)
	//void ServerEquip(AIOGear* Item);

	//UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	//void Slot(AIOEquipment* Item);

	//UFUNCTION(Reliable, Server, WithValidation)
	//void ServerSlot(AIOEquipment* Item);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerRemoveAndDestroy(AIOEquipment* Item);

	//UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	//void OnRep_Gear(TArray<AIOGear*> PreReplicationEquipment);

	UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	void OnRep_Wearables(TArray<AIOEquipment*> PreReplicationWearables);

	UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	void OnRep_Slotables(TArray<AIOEquipment*> PreReplicationSlotables);

	void ShowEquipmentMenu();

	void HideEquipmentMenu();

	UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	void EquipWearable(AIOEquipment* NewWearable);
	
	UFUNCTION(BlueprintCallable, Category = "IO|Equipment")
	void EquipSlotable(AIOEquipment* NewSlotable);

	//float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(Unreliable, Client)
	void CalculateHitDirection(FDamageEvent const& DamageEvent, class AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitEvent(FVector HitDirection);

	virtual void OnDeath() override;

	UFUNCTION(BlueprintCallable)
	void DropCoin();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDropCoin(FVector Origin, FVector ShootDir);
};

