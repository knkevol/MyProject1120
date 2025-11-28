// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

class UAIPerceptionComponent;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieAIController();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "1128")
	TObjectPtr<UAIPerceptionComponent> Perception;

	UFUNCTION()
	void ProcessPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessPerceptionForget(AActor* Actor);

	UFUNCTION()
	void FActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1128")
	TObjectPtr<UBehaviorTree> RunBTAsset;
};
