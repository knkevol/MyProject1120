// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyCharacter_Zombie.h"
#include "MyBTTask_CheckDistance.generated.h"

UENUM(BlueprintType)
enum class ECondition : uint8
{
	LessThan = 0 UMETA(DisplayName = "<"),
	GraterThan = 1 UMETA(DisplayName = ">"),
};


/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UMyBTTask_CheckDistance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_CheckDistance();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1128")
	ECondition TargetCondition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1128")
	EZombieState TargetState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1128")
	float TargetDist;
	
};
