// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGameGS.generated.h"

//BP not use
DECLARE_DELEGATE_OneParam(FOnChangedInGameConnectionCount, const int32);

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API AInGameGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	//Replicate 시 무조건 재정의 필요
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_InGameConnectionCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = 1208, ReplicatedUsing = "OnRep_InGameConnectionCount")
	int32 InGameCount = 0;

	
	FOnChangedInGameConnectionCount OnChangeInGameCount;


	void UpdateInGameCount(int32 ConnectCount);
	
};
