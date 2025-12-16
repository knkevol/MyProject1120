// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"
#include "InGameGS.h"
#include "InGameGM.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "../MyCharacter.h"

void UInGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AInGameGS* GS = Cast<AInGameGS>(UGameplayStatics::GetGameState(GetWorld()));
	if (GS)
	{
		GS->OnChangeInGameCount.BindUObject(this, &UInGameWidget::ProcessChangeInGameCount);
	}

	AInGameGM* GM = Cast<AInGameGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->CheckInGameCount();
	}

	APlayerController* PC = Cast<APlayerController>(GetOwningPlayer());
	if (PC)
	{
		AMyCharacter* Pawn = Cast<AMyCharacter>(PC->GetPawn());
		if (Pawn)
		{
			Pawn->OnHpChanged.AddDynamic(this, &UInGameWidget::ProcessHPBar);
			Pawn->OnRep_CurHP();
		}
	}
}

void UInGameWidget::ProcessChangeInGameCount(int32 InChangeGameCount)
{
	if (InGameCount)
	{
		FString Temp = FString::Printf(TEXT("%d명 생존"), InChangeGameCount);
		InGameCount->SetText(FText::FromString(Temp));
	}
}

void UInGameWidget::ProcessHPBar(float InPercent)
{
	if (HPBar)
	{
		
		HPBar->SetPercent(InPercent);
		
	}
}
