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

	void UpdatePlayerList();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGnirutPlayerListItem> PlayerListItemClass;

	TMap<int32, UGnirutPlayerListItem*> PlayerListItemByPlayerID;

};
