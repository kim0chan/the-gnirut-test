// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/UnrealNetwork.h"
#include "ObjectiveItem.h"
#include "GnirutHumanPlayer.h"
#include "Components/StaticMeshComponent.h"

AObjectiveItem::AObjectiveItem()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
	OccupyingPlayer = nullptr;
	IsOccupied = false;
	OccupiedTime = 0.0f;
	HeightOffset = 50.0f;
}

void AObjectiveItem::BeginPlay()
{
	Super::BeginPlay();
}

void AObjectiveItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AObjectiveItem, OccupyingPlayer, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AObjectiveItem, IsOccupied, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AObjectiveItem, OccupiedTime, COND_OwnerOnly);
}

void AObjectiveItem::OccupyItem(AGnirutHumanPlayer* Player)
{
	if (IsOccupied)		return;

	//SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	OccupyingPlayer = Player;
	IsOccupied = true;
	Player->HoldingItem = this;
}

void AObjectiveItem::UpdateOccupiedTime(float DeltaTime)
{
	;
}

void AObjectiveItem::DropItem()
{
	if (!IsOccupied)	return;
	if (!HasAuthority()) return;

	FVector DropLocation = GetActorLocation() + FVector(0, 0, -HeightOffset);
	SetActorLocation(DropLocation);
	IsOccupied = false;
	OccupyingPlayer = nullptr;
	SetActorEnableCollision(true);
}
/*
void AObjectiveItem::ServerDropItem_Implementation()
{
	
}

void AObjectiveItem::MulticastDropItem_Implementation()
{

}
*/

void AObjectiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsOccupied)
	{
		FRotator NewRotation = GetActorRotation() + FRotator(0, 200.0f * DeltaTime, 0);
		SetActorRotation(NewRotation);
	}
}
