// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_CheckDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_CheckDistance::UMyBTTask_CheckDistance()
{
	NodeName = TEXT("CheckDistance");
}

EBTNodeResult::Type UMyBTTask_CheckDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	AMyCharacter_Zombie* Zombie = Cast<AMyCharacter_Zombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Player && Zombie)
	{
		FVector ZombieLocation = Zombie->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();
		float Dist = FVector::Distance(ZombieLocation, PlayerLocation);

		switch (TargetCondition)
		{
		case ECondition::GraterThan:
		{
			if (Dist > TargetDist)
			{
				Zombie->SetState(TargetState);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)TargetState);
			}

		}
		break;
		case ECondition::LessThan:
		{
			if (Dist < TargetDist)
			{
				Zombie->SetState(TargetState);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)TargetState);
			}
			
		}
		break;
		}
	}

	return EBTNodeResult::Type();
}
