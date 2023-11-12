// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyPlayerController();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void HostServer();
	void JoinServer(FString address);

	bool IsValidIPAddress(const FString& IPAddress);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ULobbyPlayerHUD> PlayerHUDClass;

	UPROPERTY()
	ULobbyPlayerHUD* PlayerHUD;
};
