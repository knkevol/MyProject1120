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
		GS->OnInGameChangeConnectionCount.AddDynamic(this, &UInGameWidget::UpdateInGameConnectionCount);
	}
}

void UInGameWidget::UpdateInGameConnectionCount(int32 InConnectionCount)
{
	if (InGameConnectionCount)
	{
		FString Message = FString::Printf(TEXT("%d명 플레이"), InConnectionCount);
		InGameConnectionCount->SetText(FText::FromString(Message));
	}
}
