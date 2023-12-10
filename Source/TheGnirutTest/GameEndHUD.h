// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndHUD.generated.h"

enum class EVictoryCondition : uint8;

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UGameEndHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetWinnerTextBlock(FString WinnerName);

	void SetVictoryConditionTextBlock(EVictoryCondition Condition);

	void SetBackToWaitingButtonVisibility(ESlateVisibility InVisibility);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* WinnerTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* VictoryConditionTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BackToWaitingButton;

	UFUNCTION()
	void OnBackToWaitingButtonClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* LeaveButton;

	UFUNCTION()
	void OnLeaveButtonClicked();
};
