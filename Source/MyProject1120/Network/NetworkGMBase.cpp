// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGMBase.h"
#include "MyProject1120/MyProject1120.h"
#include "../Network/NetworkUtil.h"

void ANetworkGMBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void ANetworkGMBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

APlayerController* ANetworkGMBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void ANetworkGMBase::BeginPlay()
{
	NET_LOG(TEXT("Hello"));
	Super::BeginPlay();
}
