// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGS.h"
#include "Net/UnrealNetwork.h"

void AInGameGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGameGS, InGameCounts);
}

void AInGameGS::OnRep_InGameCount()
{
	OnChangeInGameCount.ExecuteIfBound(InGameCounts);
}


void AInGameGS::UpdateInGameCount(int32 ConnectCount)
{
	InGameCounts = ConnectCount;
	OnRep_InGameCount();

}