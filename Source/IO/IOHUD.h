// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "Characters/XLCharacter.h"
#include "GameFramework/HUD.h"
#include "IOHUD.generated.h"

UCLASS()
class AIOHUD : public AHUD
{
	GENERATED_BODY()

public:
	AIOHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

