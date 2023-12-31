// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GnirutPlayerListItem.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UGnirutPlayerListItem : public UUserWidget
{
	GENERATED_BODY()

	bool bIsLocalPlayer = false;
public:
	void SetPlayerNameTextBlock(FText playerName);

	void SetIsAlive(bool isAlive);

	void SetIsLocalPlayer(bool isLocalPlayer);

	void SetKillsTextBlock(int32 HumanPlayerKills, int32 AIPlayerKills);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerNameTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* IsAliveTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* KillsTextBlock;
};
