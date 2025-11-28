// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MyCharacter.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter_Zombie.h"

AZombieAIController::AZombieAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 300.0f;
	Sight->LoseSightRadius = 400.0f;
	Sight->PeripheralVisionAngleDegrees = 45.0f; //ÇÑÂÊ´«±âÁØ
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());


}

void AZombieAIController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (RunBTAsset)
	{
		RunBehaviorTree(RunBTAsset);
	}

	Perception->OnPerceptionUpdated.AddDynamic(this, &AZombieAIController::ProcessPerceptionUpdated);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieAIController::ProcessActorPerception);
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AZombieAIController::ProcessPerceptionForget);
	Perception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombieAIController::FActorPerceptionInfo);
	SetGenericTeamId(3);
}

void AZombieAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AZombieAIController::ProcessPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (auto Actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProcessPerception Updated %s"), *Actor->GetName());
	}
	
}

void AZombieAIController::ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus)
{
	
	//UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerception %s %s"), *Actor->GetName(), *Stimulus.Type.Name.ToString());

	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(Actor);
		AMyCharacter_Zombie* Zombie = Cast<AMyCharacter_Zombie>(GetPawn());
		if (Player)
		{
			
			Blackboard->SetValueAsObject(TEXT("Target"), Player);
			Zombie->SetState(EZombieState::Chase);
		}
	}
}

void AZombieAIController::ProcessPerceptionForget(AActor* Actor)
{
	//UE_LOG(LogTemp, Warning, TEXT("ProcessPerception Forget %s"), *Actor->GetName());

	AMyCharacter* Player = Cast<AMyCharacter>(Actor);
	AMyCharacter_Zombie* Zombie = Cast<AMyCharacter_Zombie>(GetPawn());
	if (Player && Zombie)
	{

		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		Zombie->SetState(EZombieState::Normal);
	}
}

void AZombieAIController::FActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("FActorPerceptionInfo %s"), *UpdateInfo.Target->GetName());


}
