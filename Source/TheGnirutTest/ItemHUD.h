// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UItemHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnRemainingTimeChange(const FString& NewRemainingTime);

	UFUNCTION()
	void UpdateTextBlock(const FString& Content);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RemainingTimeTextBlock;
};
