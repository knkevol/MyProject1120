// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_GetDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UMyBTService_GetDistance::UMyBTService_GetDistance()
{
	NodeName = TEXT("GetDistance");
}

void UMyBTService_GetDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (Target)
	{
		FVector ZombieLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLocation = Target->GetActorLocation();
		float Dist = FVector::Dist2D(ZombieLocation, PlayerLocation);


		FVector ZombieLoc = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLoc = Target->GetActorLocation();

		FVector vVector = PlayerLoc - ZombieLoc;
		FRotator NewRotation = vVector.Rotation();

		OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(NewRotation);

		UE_LOG(LogTemp, Warning, TEXT("UMyBTService_GetDistance %f"), Dist);

	}

	
}
