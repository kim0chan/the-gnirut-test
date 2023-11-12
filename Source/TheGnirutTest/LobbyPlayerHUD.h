// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API ULobbyPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditableTextBox* PlayerNameEditableTextBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* HostServerButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* JoinServerButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* JoinAddressEditableTextBox;

	UFUNCTION()
	void OnHostServerButtonClicked();

	UFUNCTION()
	void OnJoinServerButtonClicked();
};
