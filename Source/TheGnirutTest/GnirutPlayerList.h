// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GnirutPlayerList.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UGnirutPlayerList : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* PlayerScrollBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NumberOfHumanPlayersTextBlock;

	void UpdateNumberOfHumanPlayers(int nums);

	void UpdatePlayerList();

	void UpdatePlayerAlive(int32 PlayerID, bool isAlive);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGnirutPlayerListItem> PlayerListItemClass;

	TMap<int32, UGnirutPlayerListItem*> PlayerListItemByPlayerID;

};
