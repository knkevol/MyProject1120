// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUserWidget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UTitleUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Widget, meta =(WidgetBind))
	TObjectPtr<UButton> StartServerButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UButton> ConnectButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UEditableTextBox> UserID_1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UEditableTextBox> Password;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UEditableTextBox> ServerIP_1;

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartServer();

	UFUNCTION()
	void Connect();

	
};
