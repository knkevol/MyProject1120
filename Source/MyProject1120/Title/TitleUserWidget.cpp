// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "DataGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ServerIP_1 = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIP_1")));

	StartServerButton->OnClicked.AddDynamic(this, &UTitleUserWidget::StartServer);
	ConnectButton->OnClicked.AddDynamic(this, &UTitleUserWidget::Connect);
}

void UTitleUserWidget::StartServer()
{
	SaveData();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, TEXT("listen"));
}

void UTitleUserWidget::Connect()
{
	SaveData();
	UGameplayStatics::OpenLevel(GetWorld(), FName(ServerIP_1->GetText().ToString()), true, TEXT("Option"));

}

void UTitleUserWidget::SaveData()
{
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	if (GI)
	{
		UDataGameInstanceSubsystem* MySubsystem = GI->GetSubsystem<UDataGameInstanceSubsystem>();
		MySubsystem->UserID_1 = UserID_1->GetText().ToString();
		MySubsystem->Password = Password->GetText().ToString();
	}
}

