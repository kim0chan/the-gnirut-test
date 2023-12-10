// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDefeatHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UGameDefeatHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDefeatedTextBlock(FString AttackerName);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DefeatedTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SpectateButton;

	UFUNCTION()
	void OnSpectateButtonClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* LeaveButton;

	UFUNCTION()
	void OnLeaveButtonClicked();
};
