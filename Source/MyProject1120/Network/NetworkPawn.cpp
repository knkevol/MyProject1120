// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkPawn.h"
#include "NetworkUtil.h"

// Sets default values
ANetworkPawn::ANetworkPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANetworkPawn::PostNetInit()
{
	NET_LOG(TEXT("Begin"));
	Super::PostNetInit();
	NET_LOG(TEXT("End"));
}

void ANetworkPawn::PossessedBy(AController* NewController)
{
	NET_LOG(TEXT("Begin"));
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		FString Temp = FString::Printf(TEXT("Owner : %s"), *OwnerActor->GetName());
		NET_LOG(Temp);
	}
	else
	{
		NET_LOG(TEXT("No Owner"));
	}
	NET_LOG(TEXT("End"));

	Super::PossessedBy(NewController);

	NET_LOG(TEXT("Begin"));
	OwnerActor = GetOwner();
	if (OwnerActor)
	{
		FString Temp = FString::Printf(TEXT("Owner : %s"), *OwnerActor->GetName());
		NET_LOG(Temp);
	}
	else
	{
		NET_LOG(TEXT("No Owner"));
	}
	NET_LOG(TEXT("End"));
}

void ANetworkPawn::OnRep_Owner()
{
	NET_LOG(TEXT("Begin"));
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		FString Temp = FString::Printf(TEXT("Owner : %s"), *OwnerActor->GetName());
		NET_LOG(Temp);
	}
	else
	{
		NET_LOG(TEXT("No Owner"));
	}
	NET_LOG(TEXT("End"));

	Super::OnRep_Owner();

	NET_LOG(TEXT("Begin"));
	OwnerActor = GetOwner();
	if (OwnerActor)
	{
		FString Temp = FString::Printf(TEXT("Owner : %s"), *OwnerActor->GetName());
		NET_LOG(Temp);
	}
	else
	{
		NET_LOG(TEXT("No Owner"));
	}
	NET_LOG(TEXT("End"));
}

