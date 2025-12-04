// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPC.h"
#include "LobbyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"
#include "LobbyGM.h"

ALobbyPC::ALobbyPC()
{
}

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	if (LobbyWidgetClass)
	{
		if (IsLocalPlayerController())
		{
			UE_LOG(LogTemp, Warning, TEXT("ALobbyPC::BeginPlay"));
			LobbyWidgetObject = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
			LobbyWidgetObject->AddToViewport();

			//ListenServer일때만 실행
			//PC가 있고 GameMode가 있다 => 리슨서버
			ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GM)
			{
				GM->CheckConnectionCount();
			}
		}
	}
}

void ALobbyPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ALobbyPC::C2S_SendMessage_Validate(const FText& Message)
{
	//서버에서만 실행된다.
	return false;
}

void ALobbyPC::C2S_SendMessage_Implementation(const FText& Message)
{
	//Iterator 안돌리면 본인거 본인만 보임(서버를 통해 분산되지 않음)
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
			PC->S2C_SendMessage(Message); //모든 PC에 Message 던져줌
		}
	}
	
}

void ALobbyPC::S2C_SendMessage_Implementation(const FText& Message)
{
}
