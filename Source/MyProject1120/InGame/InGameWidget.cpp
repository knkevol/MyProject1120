// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"
#include "InGameGS.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UInGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AInGameGS* GS = Cast<AInGameGS>(UGameplayStatics::GetGameState(GetWorld()));
	if (GS)
	{
		GS->OnChangeInGameCount.BindUObject(this, &UInGameWidget::ProcessChangeInGameCount);
	}
}

void UInGameWidget::UpdateInGameConnectionCount(int32 InConnectionCount)
{
	if (InGameConnectionCount)
	{
		FString Message = FString::Printf(TEXT("%d명 생존"), InConnectionCount);
		InGameConnectionCount->SetText(FText::FromString(Message));
	}
}

void UInGameWidget::ProcessChangeInGameCount(int32 InConnectionCount)
{
	if (InGameConnectionCount)
	{
		FString Temp = FString::Printf(TEXT("%d명 생존"), InConnectionCount);
		InGameConnectionCount->SetText(FText::FromString(Temp));
	}
}
