// Fill out your copyright notice in the Description page of Project Settings.


#include "PCMBase.h"
#include "MyCharacter.h"

APCMBase::APCMBase()
{
}

void APCMBase::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	AMyCharacter* Pawn = Cast<AMyCharacter>(GetOwningPlayerController()->GetPawn());
	if (Pawn)
	{
		if (Pawn->bIsZoom)
		{
			SetFOV(60.0f);
		}
		else
		{
			SetFOV(90.f);
		}
	}
}
