// Fill out your copyright notice in the Description page of Project Settings.


#include "IOBelt.h"
#include "Net/UnrealNetwork.h"
#include "IOEquipment.h"

void AIOBelt::SelectEquipmentSlot(AIOEquipment* NewEquipment)
{

}

void AIOBelt::OnRep_Equipment(TArray<AIOEquipment*> PreReplicationEquipment)
{
	//for (int32 i = 0; i < Equipment.Num(); i++)
	//{
	//	if (Equipment[i])
	//	{
	//		Equipment[i]->Equip(Equipment[i]->AssignedSocket);
	//	}
	//}
}

//void AIOBelt::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	//DOREPLIFETIME(AIOBelt, Equipment);
//}