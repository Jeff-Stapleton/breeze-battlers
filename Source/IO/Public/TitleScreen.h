// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLiftClientSDK/Public/GameLiftClientObject.h"
#include "GameLiftClientSDK/Public/GameLiftClientApi.h"
#include "Components/Button.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TitleScreen.generated.h"

class UButton;
class UGameLiftClientObject;
class FEvent;

UCLASS(BlueprintType)
class IO_API UTitleScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTitleScreen(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

//private:
//	UPROPERTY()
//	UButton* JoinGameButton;
//
//	UPROPERTY()
//	UGameLiftClientObject* Client;
//
//	UPROPERTY()
//	FString AccessKey;
//
//	UPROPERTY()
//	FString SecretKey;
//
//	UPROPERTY()
//	FString QueueName;
//
//	UPROPERTY()
//	FString Region;
//
//	UPROPERTY()
//	bool JoinedGameSuccessfully;
//
//	FEvent* DescribeGameSessionQueuesEvent;
//
//	FEvent* SearchGameSessionsEvent;
//
//	FEvent* CreatePlayerSessionEvent;
//
//	FEvent* StartGameSessionPlacementEvent;
//
//	FEvent* DescribeGameSessionPlacementEvent;
//
//	UFUNCTION()
//	void JoinGame();
//
//	UFUNCTION()
//	void DescribeGameSessionQueues(const FString& QueueNameInput);
//
//	UFUNCTION()
//	void OnDescribeGameSessionQueuesSuccess(const TArray<FString>& FleetARNs);
//
//	UFUNCTION()
//	void OnDescribeGameSessionQueuesFailed(const FString& ErrorMessage);
//
//	UFUNCTION()
//	void SearchGameSessions(const FString& FleetId);
//
//	UFUNCTION()
//	void OnSearchGameSessionsSuccess(const TArray<FString>& GameSessionIds);
//
//	UFUNCTION()
//	void OnSearchGameSessionsFailed(const FString& ErrorMessage);
//
//	UFUNCTION()
//	void CreatePlayerSession(const FString& GameSessionId, const FString& PlayerSessionId);
//
//	UFUNCTION()
//	void OnCreatePlayerSessionSuccess(const FString& IPAddress, const FString& Port, const FString& PlayerSessionID, const FString& PlayerSessionStatus);
//
//	UFUNCTION()
//	void OnCreatePlayerSessionFailed(const FString& ErrorMessage);
//
//	UFUNCTION()
//	void StartGameSessionPlacement(const FString& QueueNameInput, const int& MaxPlayerCount, const FString& PlacementId);
//
//	UFUNCTION()
//	void OnStartGameSessionPlacementSuccess(const FString& GameSessionId, const FString& PlacementId, const FString& Status);
//
//	UFUNCTION()
//	void OnStartGameSessionPlacementFailed(const FString& ErrorMessage);
//
//	UFUNCTION()
//	void DescribeGameSessionPlacement(const FString& PlacementId);
//
//	UFUNCTION()
//	void OnDescribeGameSessionPlacementSuccess(const FString& GameSessionId, const FString& PlacementId, const FString& Status);
//
//	UFUNCTION()
//	void OnDescribeGameSessionPlacementFailed(const FString& ErrorMessage);
//
//	FString GenerateRandomId();
};