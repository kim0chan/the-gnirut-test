// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GnirutGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UGnirutGameInstance : public UGameInstance
{
	GENERATED_BODY()

	FString playerName;
public:
	virtual void Init() override;

	void SetPlayerName(FString name) { playerName = name; }
	FString GetPlayerName() { return playerName; }
};
