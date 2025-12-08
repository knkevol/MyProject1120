// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGM.h"
#include "InGameGS.h"
#include "../MyCharacter.h"

AInGameGM::AInGameGM()
{
}

void AInGameGM::BeginPlay()
{
	// no use
	Super::BeginPlay();
	//위젯존재안함 
	//CheckInGameConnectionCount();
}

void AInGameGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	CheckInGameCount();
}

void AInGameGM::Logout(AController* Exiting)
{
	CheckInGameCount();

	Super::Logout(Exiting);
}

int32 AInGameGM::CheckInGameCount()
{
	int32 PCCnt= 0;
	int32 InCount = 0;
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		++PCCnt;
		AMyCharacter* Pawn = Cast<AMyCharacter>((*Iter)->GetPawn());
		if (Pawn)
		{
			if (Pawn->CurHp > 0)
			{
				InCount++;
			}
		}
	}


	
	AInGameGS* GS = GetGameState<AInGameGS>();
	if (GS)
	{
		GS->UpdateInGameCount(InCount);
	}

	FTimerHandle EndTimer;


	if (PCCnt >= 2 && InCount == 1)
	{
		GetWorld()->GetTimerManager().SetTimer(EndTimer,
			FTimerDelegate::CreateLambda([this]() {
				GetWorld()->ServerTravel(TEXT("Lobby"));
				}),
			10.0f,
			false,
			0.0f
		);
	}
	

	return InCount;
}