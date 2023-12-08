// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TabkeyPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UTabkeyPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void ToggleVisibility();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LeaveButton;

	UFUNCTION()
	void OnLeaveButtonClicked();
};
