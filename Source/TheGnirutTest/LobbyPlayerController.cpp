// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "LobbyPlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Networking.h"
#include <regex>

bool ALobbyPlayerController::IsValidIPAddress(const FString& IPAddress)
{
	// 정규 표현식을 사용하여 IP 주소의 유효성을 체크
	std::regex ipRegex(R"(\b(?:\d{1,3}\.){3}\d{1,3}\b)");

	// FString을 std::string으로 변환
	std::string ipAddressStr(TCHAR_TO_UTF8(*IPAddress));

	// 정규 표현식과 매치하는지 확인
	return std::regex_match(ipAddressStr, ipRegex);
}

ALobbyPlayerController::ALobbyPlayerController()
{
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<ULobbyPlayerHUD>(this, PlayerHUDClass);
		if (PlayerHUD) {
			PlayerHUD->AddToViewport();
		}
	}
}

void ALobbyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void ALobbyPlayerController::HostServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("WaitingMap"), true, ((FString)(L"Listen")));
}

void ALobbyPlayerController::JoinServer(FString address)
{
	//FName("127.0.0.1")
	//UGameplayStatics::OpenLevel(GetWorld(), FName(address));

	if (IsValidIPAddress(address))
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(address));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid IP Address: %s"), *address);
	}
}
