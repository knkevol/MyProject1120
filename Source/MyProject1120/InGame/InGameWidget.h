// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void UpdateInGameConnectionCount(int32 InConnectionCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component, meta = (WidgetBind))
	TObjectPtr <UTextBlock> InGameConnectionCount;
	
};
