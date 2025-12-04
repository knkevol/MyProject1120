// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePC.h"
#include "TitleUserWidget.h"

void ATitlePC::BeginPlay()
{
	Super::BeginPlay();

	//경로설정
	FSoftClassPath TitleWidgetBase(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyProj1120/Title/WBP_TitleWidget.WBP_TitleWidget_C'"));

	//class 정의
	UClass* WidgetClass = TitleWidgetBase.TryLoadClass<UTitleUserWidget>();
	if (WidgetClass)
	{
		TitleWidgetObject = CreateWidget<UTitleUserWidget>(this, WidgetClass);
		if (TitleWidgetObject)
		{
			TitleWidgetObject->AddToViewport();
		}
	}

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}

void ATitlePC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}
