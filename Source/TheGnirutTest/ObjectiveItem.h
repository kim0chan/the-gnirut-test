// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemHUD.h"
#include "ObjectiveItem.generated.h"

class UItemHUD;

UCLASS()
class THEGNIRUTTEST_API AObjectiveItem : public AActor
{
	GENERATED_BODY()

public:
	AObjectiveItem();

	float HeightOffset;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* ItemWidget;

	UPROPERTY(Replicated)
	bool IsOccupied;

	UPROPERTY(Replicated)
	float RemainingTime;

	UPROPERTY(Replicated)
	FString DisplayText;

	UPROPERTY(Replicated)
	class AGnirutHumanPlayer* OccupyingPlayer;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BoxMesh;

	UFUNCTION()
	void OccupyItem(class AGnirutHumanPlayer* Player);

	UFUNCTION()
	void UnOccupyItem();

	UFUNCTION()
	void UpdateRemainingTime(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerUpdateRemainingTime(float Time);
	void ServerUpdateRemainingTime_Implementation(float Time);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateRemainingTime(float Time);
	void MulticastUpdateRemainingTime_Implementation(float Time);

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;
};
