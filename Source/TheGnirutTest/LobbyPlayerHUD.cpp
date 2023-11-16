// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerHUD.h"
#include "LobbyPlayerController.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
//#include "GameFramework/PlayerState.h"

void ULobbyPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	HostServerButton->OnClicked.AddDynamic(this, &ThisClass::OnHostServerButtonClicked);
	JoinServerButton->OnClicked.AddDynamic(this, &ThisClass::OnJoinServerButtonClicked);
	//PlayerNameEditableTextBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnPlayerNameEditableTextBoxCommited);
	JoinAddressEditableTextBox->SetHintText(FText::FromString("IP address to join in"));
	JoinAddressEditableTextBox->SetText(FText::FromString("127.0.0.1"));
}

//void ULobbyPlayerHUD::OnPlayerNameEditableTextBoxCommited(const FText& Text, ETextCommit::Type CommitMethod)
//{
//	if (APlayerState* PS = GetOwningPlayerState())
//	{
//		FString newName = Text.ToString();
//		if (!newName.IsEmpty()) PS->SetPlayerName(newName);
//	}
//}

void ULobbyPlayerHUD::OnHostServerButtonClicked()
{
	ALobbyPlayerController* LPC = Cast<ALobbyPlayerController>(GetOwningPlayer());
	if (LPC)
	{
		LPC->HostServer();
	}
}

void ULobbyPlayerHUD::OnJoinServerButtonClicked()
{
	ALobbyPlayerController* LPC = Cast<ALobbyPlayerController>(GetOwningPlayer());
	if (LPC)
	{
		FText address = JoinAddressEditableTextBox->GetText();
		LPC->JoinServer(address.ToString());
	}
}
