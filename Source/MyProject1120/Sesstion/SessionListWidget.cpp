

#include "SessionListWidget.h"
#include "SessionItemWidget.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "FindSessionsCallbackProxy.h"


bool USessionListWidget::Initialize()
{
	if (Super::Initialize() == false)
		return false;

	SetInfo();

	return true;
}

void USessionListWidget::SetInfo()
{
	Sessions.Empty();

	for (int i = 0; i < 10; i++)
	{
		if (SessionItemClass == nullptr)
			continue;

		USessionItemWidget* ChildWidget = CreateWidget<USessionItemWidget>(GetWorld(), SessionItemClass);
		if (ChildWidget == nullptr)
			continue;

		// Wapbox(UI)에 차일드 위젯 붙이기
		SessionList->AddChildToWrapBox(ChildWidget);

		// 데이터로써 만들어진 차일드 들고있기
		Sessions.Add(ChildWidget);
	}

	RefreshUI();
}

void USessionListWidget::RefreshUI()
{
	// 실제 접속자 몇명인지 확인
	const int32 SessionLength = SessionInfos.Num();

	for (int32 i = 0; i < 10; i++)
	{
		const int32 Index = i;

		if (Index < SessionLength) // 접속자 인덱스
		{
			// 차일드 UI 켜주기
			Sessions[Index]->SetVisibility(ESlateVisibility::Visible);
			FBlueprintSessionResult Result = SessionInfos[Index];
			Sessions[Index]->SetInfo(Result);
		}
		else // 접속하지 않은 인덱스
		{
			// 차일드 UI 꺼주기
			Sessions[Index]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}