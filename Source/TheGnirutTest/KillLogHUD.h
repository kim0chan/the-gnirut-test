// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KillLogHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API UKillLogHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetKillLogTextBlock(const FString& Content);
	void ShowKillLogTextBlock();
	void HideKillLogTextBlock();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* KillLogTextBlock;
	
private:
	FTimerHandle KillLogTimerHandle;
	float KillLogDIsplayDuration = 3.0f;
};
