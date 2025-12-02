// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkPC.h"
#include "NetworkUtil.h"

void ANetworkPC::BeginPlay()
{
	NET_LOG(TEXT("Begin"));
	Super::BeginPlay();

	//Local
	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		NET_LOG(TEXT("ENetRole::ROLE_Authority"));
	}
	else if (GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		NET_LOG(TEXT("ENetRole::ROLE_AutonomousProxy"));
	}
	else if (GetLocalRole() == ENetRole::ROLE_SimulatedProxy)
	{
		NET_LOG(TEXT("ENetRole::ROLE_SimulatedProxy"));
	}

	//Remote
	if (GetRemoteRole() == ENetRole::ROLE_Authority)
	{
		NET_LOG(TEXT("GetRemoteRole == ENetRole::ROLE_Authority"));
	}
	else if (GetRemoteRole() == ENetRole::ROLE_AutonomousProxy)
	{
		NET_LOG(TEXT("GetRemoteRole == ENetRole::ROLE_AutonomousProxy"));
	}
	else if (GetRemoteRole() == ENetRole::ROLE_SimulatedProxy)
	{
		NET_LOG(TEXT("GetRemoteRole == ENetRole::ROLE_SimulatedProxy"));
	}


	NET_LOG(TEXT("End"));

}

void ANetworkPC::PostNetInit()
{
	NET_LOG(TEXT("Begin"));
	Super::PostNetInit();
	NET_LOG(TEXT("End"));
}
