// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IOAttachedEquipment.generated.h"

UCLASS()
class IO_API AIOAttachedEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIOAttachedEquipment();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	USceneComponent* Root;
};
