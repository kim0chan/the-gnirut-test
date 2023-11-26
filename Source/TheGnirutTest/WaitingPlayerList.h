// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitingPlayerList.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UWaitingPlayerList : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* PlayerScrollBox;

	void UpdatePlayerList();

	void UpdatePlayerReady(int32 PlayerID, bool isReady);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWaitingPlayerListItem> PlayerListItemClass;
	
	TMap<int32, UWaitingPlayerListItem*> PlayerListItemByPlayerID;
};
