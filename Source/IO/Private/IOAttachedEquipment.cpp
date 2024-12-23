// Fill out your copyright notice in the Description page of Project Settings.


#include "IOAttachedEquipment.h"

// Sets default values
AIOAttachedEquipment::AIOAttachedEquipment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionObjectType(ECC_WorldStatic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetupAttachment(Root);

	bReplicates = true;
}


