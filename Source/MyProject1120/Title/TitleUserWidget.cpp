// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ServerIP_1 = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIP_1")));

	StartServerButton->OnClicked.AddDynamic(this, &UTitleUserWidget::StartServer);
	ConnectButton->OnClicked.AddDynamic(this, &UTitleUserWidget::Connect);
}

void UTitleUserWidget::StartServer()
{

}

void UTitleUserWidget::Connect()
{

}

