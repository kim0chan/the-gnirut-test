// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGnirutPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AAGnirutPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
