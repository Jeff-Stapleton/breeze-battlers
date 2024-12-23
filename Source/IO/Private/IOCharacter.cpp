// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "IOCharacter.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/InputSettings.h"
#include "Net/UnrealNetwork.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

#include "IO.h"
#include "IOProjectile.h"
#include "IOBelt.h"
#include "Components/Character/XLMovementComponent.h"
#include "Pickups/XLPickup.h"
#include "Controllers/XLPlayerController.h"
#include "Managers/XLPlayerCameraManager.h"
#include "IOAttachedEquipment.h"
#include "IOEquipment.h"

AIOCharacter::AIOCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXLMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	DeathDelegate.AddDynamic(this, &AIOCharacter::DropCoin);
	Coins = 0.0f;
}

void AIOCharacter::BeginPlay()
{
	Super::BeginPlay();

	UGameViewportClient* viewport = GetWorld()->GetGameViewport();
	if (viewport)
	{
		viewport->RemoveAllViewportWidgets();
	}

	if (Controller)
	{
		AXLPlayerController* PlayerController = Cast<AXLPlayerController>(Controller);
		if (PlayerController && PlayerController->PlayerCameraManager)
		{
			AXLPlayerCameraManager* CameraManager = Cast<AXLPlayerCameraManager>(PlayerController->PlayerCameraManager);
			CameraManager->TargetFOV = CameraManager->NormalFOV;
		}
	}

	if (HUDWidget)
	{
		UUserWidget* HUD = CreateWidget<UUserWidget>(GetWorld(), HUDWidget, TEXT("HUD"));
		HUD->AddToViewport();
	}
	//SpawnInventory();
}

void AIOCharacter::SpawnInventory()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Unarmed = GetWorld()->SpawnActor<AIOEquipment>(UnarmedBP, SpawnInfo);
		///Unarmed->SetOwningPawn(this);
		//Slotables.Add(Unarmed);

		// Spawn Wearables
		for (int32 i = 0; i < DefaultWearables.Num(); i++)
		{
			if (DefaultWearables[i])
			{
				AIOEquipment* NewWearable = GetWorld()->SpawnActor<AIOEquipment>(DefaultWearables[i], SpawnInfo);
				NewWearable->SetOwningPawn(this);

				EquipWearable(NewWearable);
			}
		}

		// Spawn Slotables
		for (int32 i = 0; i < DefaultSlotables.Num(); i++)
		{
			if (DefaultSlotables[i])
			{
				AIOEquipment* NewSlotable = GetWorld()->SpawnActor<AIOEquipment>(DefaultSlotables[i], SpawnInfo);
				NewSlotable->SetOwningPawn(this);

				EquipSlotable(NewSlotable);
			}
		}
	}
}

void AIOCharacter::EquipWearable(AIOEquipment* NewWearable)
{
	for (int32 j = 0; j < WearableSlots.Num(); j++)
	{
		if (WearableSlots[j].IsEmpty && WearableSlots[j].EquipmentSlotType == NewWearable->EquipmentSlotType && NewWearable->Tags.Contains("wearable"))
		{
			NewWearable->Socket = WearableSlots[j].Socket;
			Wearables.Add(NewWearable);
			NewWearable->Attach(Head, WearableSlots[j].Socket);
			for (int32 k = 0; k < NewWearable->Attachments.Num(); k++)
			{
				Mods.Add(NewWearable->Attachments[k]);
			}
			break;
		}
	}
}

void AIOCharacter::EquipSlotable(AIOEquipment* NewSlotable)
{
	if (NewSlotable->Tags.Contains("slotable"))
	{
		for (int32 j = 0; j < Mods.Num(); j++)
		{
			if (Mods[j]->CurrentStorage < Mods[j]->StorageCapacity && Mods[j]->EquipmentSlotType == NewSlotable->EquipmentSlotType)
			{
				Mods[j]->CurrentStorage++;

				bool IsOriginal = true;
				int32 Index = 0;

				for (int32 i = 0; i < Slotables.Num(); i++)
				{
					if (Slotables[i]->Identifier == NewSlotable->Identifier)
					{
						IsOriginal = false;
						Index = i;
						//Slotables[Index]->Count++;
						break;
					}
				}

				if (IsOriginal)
				{
					//NewSlotable->Count = 1;
					NewSlotable->Attach(Head, "Hand_R");
					NewSlotable->Mesh3P->SetVisibility(false);
					Slotables.Add(NewSlotable);
					Index = Slotables.Num() - 1;
				}

				//attach it to person
				if (Slotables[Index]->UsesAttachedMeshes)
				{
					FActorSpawnParameters SpawnInfo;
					SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					AIOAttachedEquipment* Attachable = GetWorld()->SpawnActor<AIOAttachedEquipment>(Slotables[Index]->AttachedMeshTemplate, SpawnInfo);
					Slotables[Index]->AttachedMeshes.Add(Attachable);
					// Maybe needs to happen on client
					Mods[j]->Slot(Attachable);
				}
				break;
			}
		}
	}
}

bool AIOCharacter::ServerRemoveAndDestroy_Validate(AIOEquipment* Item)
{
	return true;
}

void AIOCharacter::ServerRemoveAndDestroy_Implementation(AIOEquipment* Item)
{
	if (Wearables.Contains(Item))
	{
		Wearables.Remove(Item);
		Item->Destroy();
	}
}

void AIOCharacter::ShowEquipmentMenu()
{
	if (EquipmentWidget)
	{
		IsInventoryOpen = true;
		EquipmentWheel = CreateWidget<UUserWidget>(GetWorld(), EquipmentWidget, TEXT("Equipment"));
		EquipmentWheel->AddToViewport();

		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->SetInputMode(FInputModeGameAndUI());
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}
	}
}

void AIOCharacter::HideEquipmentMenu()
{
	if (EquipmentWheel)
	{
		IsInventoryOpen = false;
		EquipmentWheel->RemoveFromParent();

		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->SetInputMode(FInputModeGameOnly());
			PC->bShowMouseCursor = false;
			PC->bEnableClickEvents = false;
			PC->bEnableMouseOverEvents = false;
		}
	}
}
//
//float AIOCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
//{
//	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
//
//	CalculateHitDirection(DamageEvent, DamageCauser);
//
//	return ActualDamage;
//}

void AIOCharacter::CalculateHitDirection_Implementation(struct FDamageEvent const& DamageEvent, class AActor* DamageCauser)
{
	if (DamageCauser)
	{
		const FVector HitVector = DamageCauser->GetActorLocation();
		OnHitEvent(HitVector);
	}
}

void AIOCharacter::OnDeath()
{	
	for (int32 i = Wearables.Num() - 1; i >= 0; i--)
	{
		AIOEquipment* Wearable = Wearables[i];
		if (Wearable)
		{
			Wearables.RemoveSingle(Wearable);
			Wearable->Destroy();
		}
	}
	for (int32 i = Slotables.Num() - 1; i >= 0; i--)
	{
		AIOEquipment* Slotable = Slotables[i];
		if (Slotable)
		{
			Slotables.RemoveSingle(Slotable);
			Slotable->Destroy();
		}
	}

	Super::OnDeath();
}

void AIOCharacter::DropCoin()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i = 0; i < Coins; i++)
		{
			const FVector Start = Head->GetSocketLocation(FName(TEXT("PopTop")));
			const FVector AimDir = Head->GetSocketRotation(FName(TEXT("PopTop"))).Vector();

			FRandomStream WeaponRandomStream(FMath::Rand());
			const float ConeHalfAngle = FMath::DegreesToRadians(45.0f);
			const FVector Destination = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);

			const FVector End = Start + Destination * 750.0f;

			ServerDropCoin(Start, End);
		}
	}
}

bool AIOCharacter::ServerDropCoin_Validate(FVector Origin, FVector ShootDir)
{
	return true;
}

void AIOCharacter::ServerDropCoin_Implementation(FVector Origin, FVector ShootDir)
{
	FTransform SpawnTM(FVector::ZeroVector.Rotation(), Origin);
	AXLPickup* Coin = Cast<AXLPickup>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PickupClass, SpawnTM));
	if (Coin)
	{
		Coin->RespawnTime = 0.0f;
		Coin->SetInstigator(this);
		Coin->SetOwner(this);
		FVector test = (ShootDir - Origin).GetSafeNormal();
		Coin->InitVelocity(test);
		Coin->SetLifeSpan(90.0f);

		UGameplayStatics::FinishSpawningActor(Coin, SpawnTM);
	}
}

void AIOCharacter::OnRep_Wearables(TArray<AIOEquipment*> PreReplicationEquipment)
{
	for (int32 i = 0; i < Wearables.Num(); i++)
	{
		if (Wearables[i])
		{
			Wearables[i]->Attach(Head, Wearables[i]->Socket);
		}
	}
}

void AIOCharacter::OnRep_Slotables(TArray<AIOEquipment*> PreReplicationEquipment)
{
	for (int32 i = 0; i < Slotables.Num(); i++)
	{
		if (Slotables[i])
		{
			Slotables[i]->Attach(Head, "Hand_R");
			Slotables[i]->Mesh3P->SetVisibility(false);
		}
	}
}

void AIOCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIOCharacter, Wearables);
	DOREPLIFETIME(AIOCharacter, Slotables);
	DOREPLIFETIME(AIOCharacter, Mods);

	DOREPLIFETIME(AIOCharacter, Coins);
	//DOREPLIFETIME_CONDITION(AIOCharacter, EquipmentWheelEquipment, COND_OwnerOnly);
}
