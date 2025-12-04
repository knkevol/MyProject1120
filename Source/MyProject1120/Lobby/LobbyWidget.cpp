// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"
#include "LobbyPC.h"
#include "LobbyGM.h"
#include "../Title/DataGameInstanceSubsystem.h"
#include "Components/RichTextBlock.h"

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ULobbyWidget::Start);
	}

	if (ChatInput)
	{
		ChatInput->OnTextCommitted.AddDynamic(this, &ULobbyWidget::ProcessOnCommit);
		ChatInput->OnTextChanged.AddDynamic(this, &ULobbyWidget::ProcessOnChange);
	}

	ALobbyGS* GS = Cast<ALobbyGS>(UGameplayStatics::GetGameState(GetWorld()));
	if (GS)
	{
		GS->OnChageLeftTime.AddDynamic(this, &ULobbyWidget::UpdateLeftTime);
		GS->OnChangeConnectionCount.AddDynamic(this, &ULobbyWidget::UpdateConnectionCount);
	}

}

void ULobbyWidget::Start()
{
	GetWorld()->ServerTravel(TEXT("InGame"));
}

void ULobbyWidget::ProcessOnCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
		case ETextCommit::OnEnter:
		{
			ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());
			if (PC)
			{
				UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
				if (GI)
				{
					UDataGameInstanceSubsystem* MySubsystem = GI->GetSubsystem<UDataGameInstanceSubsystem>();
					//MySubsystem->UserID_1
					FString Temp = FString::Printf(TEXT("% s : %s"), *MySubsystem->UserID_1, *Text.ToString());

					//Local PC Call -> Server PC Execute
					PC->C2S_SendMessage(FText::FromString(Temp));
					// OnCleared
					ChatInput->SetText(FText::FromString(TEXT("")));
				}
			}
		}
		break;
		case ETextCommit::OnCleared:
		{
			ChatInput->SetUserFocus(GetOwningPlayer());
		}
		break;
	}
}

void ULobbyWidget::ProcessOnChange(const FText& Text)
{
}

void ULobbyWidget::UpdateLeftTime(int32 InLeftTime)
{
	if (LeftTime)
	{
		if (InLeftTime < 0)
		{
			ALobbyGM* GM = GetWorld()->GetAuthGameMode<ALobbyGM>();
			GM->StopLeftTimeTimer();
			Start();
		}
		else
		{
			FString Message = FString::Printf(TEXT("%d초 남음"), InLeftTime);
			LeftTime->SetText(FText::FromString(Message));
		}
	}
}

void ULobbyWidget::UpdateConnectionCount(int32 InConnectionCount)
{
	if (ConnectionCount)
	{
		FString Message = FString::Printf(TEXT("%d명 접속"), InConnectionCount);
		ConnectionCount->SetText(FText::FromString(Message));
	}
}

void ULobbyWidget::AddMessage(const FText& Message)
{
	if (ChatScrollBox)
	{
		//UTextBlock* NewMessage = NewObject<UTextBlock>(ChatScrollBox); // NewObject == c++ new
		//if (NewMessage)
		//{
		//	NewMessage->SetText(Message);
		//	FSlateFontInfo FontInfo = NewMessage->GetFont();
		//	//Font에 다이렉트로 접근 불가하여 FontInfo로 접근해야한다.
		//	FontInfo.Size = 25;
		//	NewMessage->SetFont(FontInfo);
		//	//NewMessage->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 1)));


		//	ChatScrollBox->AddChild(NewMessage);
		//	ChatScrollBox->ScrollToEnd();
		//}
		URichTextBlock* NewMessageBlock = NewObject<URichTextBlock>(ChatScrollBox);
		if (NewMessageBlock)
		{

			NewMessageBlock->SetText(Message);
			NewMessageBlock->SetAutoWrapText(true);
			NewMessageBlock->SetWrapTextAt(ChatScrollBox->GetCachedGeometry().GetLocalSize().X);
			NewMessageBlock->SetWrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping);

			if (ChatStyleSet)
			{
				NewMessageBlock->SetTextStyleSet(ChatStyleSet);
			}

			ChatScrollBox->AddChild(NewMessageBlock);
			ChatScrollBox->ScrollToEnd();
		}
	}
}

void ULobbyWidget::ShowStartButton()
{
	if (StartButton)
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
}
