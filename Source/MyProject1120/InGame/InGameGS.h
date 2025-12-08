// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGameGS.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedInGameConnectionCount, const int32, InGameConnectionCount);

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API AInGameGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_InGameConnectionCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, ReplicatedUsing = "OnRep_InGameConnectionCount")
	int32 InGameConnectionCount = 0;

	UPROPERTY(BlueprintAssignable)
	FOnChangedInGameConnectionCount OnInGameChangeConnectionCount;
	
};
