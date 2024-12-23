// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IOGameMode.generated.h"

UCLASS(minimalapi)
class AIOGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	TSubclassOf<APawn> BotPawnClass;

	AIOGameMode();
};



