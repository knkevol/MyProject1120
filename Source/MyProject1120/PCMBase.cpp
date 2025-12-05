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
		float TargetFOV = Pawn->bIsZoom ? ZoomFOV : NormalFOV;
		float CurrentFOV = FMath::FInterpTo(GetFOVAngle(), TargetFOV, DeltaTime, ZoomSpeed);
		if (Pawn->bIsZoom)
		{
			UE_LOG(LogTemp, Warning, TEXT("APCMBase::UpdateCamera CurrentFOV"));
			SetFOV(CurrentFOV);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCMBase::UpdateCamera TargetFOV"));
			SetFOV(TargetFOV);
		}
	}
}
