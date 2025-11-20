// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	TObjectPtr<UInputMappingContext> IMC_Default;

	
};
