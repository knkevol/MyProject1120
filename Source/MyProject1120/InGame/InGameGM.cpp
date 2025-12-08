// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGM.h"
#include "InGameGS.h"
#include "InGameWidget.h"
#include "../MyCharacter.h"

AInGameGM::AInGameGM()
{
}

void AInGameGM::BeginPlay()
{
	Super::BeginPlay();
	CheckInGameConnectionCount();
}

void AInGameGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	CheckInGameConnectionCount();
}

void AInGameGM::Logout(AController* Exiting)
{
	CheckInGameConnectionCount();

	Super::Logout(Exiting);
}

int32 AInGameGM::CheckInGameConnectionCount()
{
	int32 TempCount = 0;
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AMyCharacter* Pawn = Cast<AMyCharacter>((*Iter)->GetPawn());
		if (Pawn)
		{
			if (Pawn->CurHp > 0)
			{
				TempCount++;
			}
		}
	}
	
	AInGameGS* GS = GetGameState<AInGameGS>();
	if (GS)
	{
		GS->UpdateInGameCount(TempCount);
	}

	return TempCount;
}