// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitingPlayerListItem.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UWaitingPlayerListItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void setPlayerNameTextBlock(FText playerName);

	void setIsReadyTextBlock(bool isReady);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerNameTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* IsReadyTextBlock;
};
