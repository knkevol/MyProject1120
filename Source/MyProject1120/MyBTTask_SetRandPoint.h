// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_SetRandPoint.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UMyBTTask_SetRandPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_SetRandPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
