// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveItem.generated.h"

UCLASS()
class THEGNIRUTTEST_API AObjectiveItem : public AActor
{
	GENERATED_BODY()

public:
	AObjectiveItem();

	float HeightOffset;

	UPROPERTY(Replicated)
	bool IsOccupied;

	UPROPERTY(ReplicatedUsing = OnRep_RemainingTime)
	float RemainingTime;

	UPROPERTY(Replicated)
	FString DisplayText;

	UFUNCTION()
	void OnRep_RemainingTime();

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

	virtual void DrawHUD(class APlayerController* PC, class UCanvas* Canvas, FVector2D ViewportSize);

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;
};
