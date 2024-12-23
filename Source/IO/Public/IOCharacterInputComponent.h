// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/InputComponents/XLCharacterInputComponent.h"
#include "IOCharacterInputComponent.generated.h"

class AIOPlayerController;
class APlayerController;

UCLASS()
class IO_API UIOCharacterInputComponent : public UXLCharacterInputComponent
{
	GENERATED_BODY()

public:

	virtual void Init(APlayerController* NewController) override;

	virtual void ShowEquipmentMenu();

	virtual void HideEquipmentMenu();

};
