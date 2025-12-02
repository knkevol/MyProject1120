// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePC.generated.h"

class UTitleUserWidget;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API ATitlePC : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UMG")
	TObjectPtr<UTitleUserWidget> TitleWidgetObject;
	
};
