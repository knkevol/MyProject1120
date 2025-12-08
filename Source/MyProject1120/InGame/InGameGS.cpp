// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGS.h"
#include "Net/UnrealNetwork.h"

void AInGameGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGameGS, InGameCount);
}

void AInGameGS::OnRep_InGameConnectionCount()
{
	OnChangeInGameCount.ExecuteIfBound(InGameCount);
}


void AInGameGS::UpdateInGameCount(int32 ConnectCount)
{
	InGameCount = ConnectCount;
	OnRep_InGameConnectionCount();

}