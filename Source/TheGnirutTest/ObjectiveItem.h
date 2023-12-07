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

	UPROPERTY(Replicated)
	float OccupiedTime;

	UPROPERTY(Replicated)
	class AGnirutHumanPlayer* OccupyingPlayer;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BoxMesh;

	UFUNCTION()
	void OccupyItem(class AGnirutHumanPlayer* Player);

	//UFUNCTION(Server, Reliable)
	//void ServerOccupyItem(class AGnirutHumanPlayer* Player);
	//void ServerOccupyItem_Implementation(class AGnirutHumanPlayer* Player);

	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastOccupyItem(class AGnirutHumanPlayer* Player);
	//void MulticastOccupyItem_Implementation(class AGnirutHumanPlayer* Player);

	UFUNCTION()
	void DropItem();

	//UFUNCTION(Server, Reliable)
	//void ServerDropItem();
	//void ServerDropItem_Implementation();

	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastDropItem();
	//void MulticastDropItem_Implementation();

	UFUNCTION()
	void UpdateOccupiedTime(float DeltaTime);

	//UFUNCTION(Server, Reliable)
	//void ServerUpdateOccupiedTime(float DeltaTime);
	//void ServerUpdateOccupiedTime_Implementation(float DeltaTime);

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;
};
