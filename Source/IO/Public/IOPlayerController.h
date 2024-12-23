// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/XLPlayerController.h"
#include "IOPlayerController.generated.h"

class UIOCharacterInputComponent;

UCLASS()
class IO_API AIOPlayerController : public AXLPlayerController
{
	GENERATED_BODY()
	
	UPROPERTY()
	UIOCharacterInputComponent* IOCharacterInputComponent;

	AIOPlayerController();

	virtual void SetupInputComponent() override;

	virtual void SetControllerInputMode(TEnumAsByte<EInputMode::Type> Mode) override;

};
