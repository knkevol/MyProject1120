// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_GetDistance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UMyBTService_GetDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_GetDistance();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
