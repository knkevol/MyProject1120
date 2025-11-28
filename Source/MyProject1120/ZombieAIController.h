// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieAIController();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "1128")
	TObjectPtr<UAIPerceptionComponent> Perception;
	
};
