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
	bReplicates = true;
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

void AObjectiveItem::OccupyItem(class AGnirutHumanPlayer* Player)
{
	if (IsOccupied)		return;
	if (Player)
	{
		//SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		OccupyingPlayer = Player;
		Player->SetHoldingItem(this);
		IsOccupied = true;
	}
}

void AObjectiveItem::UpdateOccupiedTime(float DeltaTime)
{
	;
}


void AObjectiveItem::UnOccupyItem()
{
	if (!IsOccupied)		return;
	IsOccupied = false;
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
	else
	{
		FVector NewLocation = OccupyingPlayer->GetActorLocation() + FVector(0, 0, HeightOffset);
		FRotator NewRotation = OccupyingPlayer->GetActorRotation();

		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}
