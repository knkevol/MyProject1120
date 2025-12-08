// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameGM.generated.h"

class UInGameWidget;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API AInGameGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void CheckInGameConnectionCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UInGameWidget> InGameWidgetObject;
	
};
