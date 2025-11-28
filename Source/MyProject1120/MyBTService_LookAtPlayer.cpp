// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_LookAtPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

UMyBTService_LookAtPlayer::UMyBTService_LookAtPlayer()
{
	NodeName = TEXT("LookPlayer");
}

void UMyBTService_LookAtPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));

	if (Player)
	{
		AActor* Zombie = OwnerComp.GetAIOwner()->GetPawn();
		FVector ZombieLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(ZombieLocation, PlayerLocation);
		TargetRotation.Pitch = 0;
		//보간. 휙 돌아가지 않도록
		FRotator TargetRotationInterpTo = FMath::RInterpTo(Zombie->GetActorRotation(), TargetRotation, DeltaSeconds, 15.0f);

		Zombie->SetActorRotation(TargetRotationInterpTo);
	}
}
