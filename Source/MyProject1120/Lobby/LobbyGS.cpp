// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyWidget.h"

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, LeftTime);
	DOREPLIFETIME(ALobbyGS, ConnectionCount);
}

void ALobbyGS::OnRep_LeftTime()
{
	OnChageLeftTime.Broadcast(LeftTime);
}

void ALobbyGS::OnRep_ConnectionCount()
{
	OnChangeConnectionCount.Broadcast(ConnectionCount);
}

void ALobbyGS::CountDownLeftTime()
{

}

void ALobbyGS::BeginPlay()
{
	Super::BeginPlay();
}
