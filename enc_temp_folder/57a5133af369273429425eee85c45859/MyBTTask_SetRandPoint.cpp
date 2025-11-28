// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_SetRandPoint.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "NavigationSystem.h"

UMyBTTask_SetRandPoint::UMyBTTask_SetRandPoint()
{
	NodeName = "SetRandPoint";
}

EBTNodeResult::Type UMyBTTask_SetRandPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	if (AIC)
	{
		FVector Location = AIC->GetPawn()->GetActorLocation();
		FVector Destination;
		if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(
			GetWorld(),
			Location,
			Destination,
			5000.0f //5m
		))
		{
			return EBTNodeResult::Succeeded;
		}
		
	}


	return EBTNodeResult::Failed;
	
}
