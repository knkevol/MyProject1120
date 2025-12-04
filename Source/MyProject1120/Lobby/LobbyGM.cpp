// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"

ALobbyGM::ALobbyGM()
{
}

void ALobbyGM::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	UE_LOG(LogTemp, Warning, TEXT("%s Option %s"), *Address, *Options);
}

APlayerController* ALobbyGM::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* PC = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	return PC;
}

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(LeftTimerHandle,
		FTimerDelegate::CreateLambda([this]() {
			ALobbyGS* GS = GetGameState<ALobbyGS>();
			if (GS)
			{
				//Server
				GS->LeftTime--;
				GS->OnRep_LeftTime();
			}
			}),
		1.0f,
		true,
		0.0f
	);

	//BeginPlay보다 UI가 늦어서 업데이트를 해준다.
	CheckConnectionCount();
}

void ALobbyGM::CheckConnectionCount()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		//PC count function = GetPlayerControllerIterator
		int32 TempCnt = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			TempCnt++;
		}
		GS->ConnectionCount = TempCnt;
		//값 바뀌면 바뀐값 복제해줌
		GS->OnRep_ConnectionCount();
	}
}
