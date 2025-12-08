// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGM.h"
#include "InGameGS.h"
#include "InGameWidget.h"

void AInGameGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	CheckInGameConnectionCount();
}

void AInGameGM::CheckInGameConnectionCount()
{

	AInGameGS* GS = GetGameState<AInGameGS>();
	if (GS)
	{
		//PC count function = GetPlayerControllerIterator
		int32 TempCount = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			TempCount++;
		}

		GS->InGameConnectionCount = TempCount;
		GS->OnRep_InGameConnectionCount();
	}
}