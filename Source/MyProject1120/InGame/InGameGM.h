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
	AInGameGM();

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	int32 CheckInGameConnectionCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UInGameWidget> InGameWidgetObject;
	
};
