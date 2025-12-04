// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UDataGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString UserID_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString Password;

	
};
