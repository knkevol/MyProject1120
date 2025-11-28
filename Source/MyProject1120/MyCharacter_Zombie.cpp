// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter_Zombie.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMyCharacter_Zombie::AMyCharacter_Zombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyCharacter_Zombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter_Zombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//switch (CurState)
	//{
	//case EZombieState::Normal:
	//	break;
	//case EZombieState::Chase:
	//	break;
	//case EZombieState::Battle:
	//	break;
	//case EZombieState::Death:
	//	break;
	//default:
	//	break;
	//}

	////Chase
	//APawn* TargetPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	//FVector Direction = TargetPawn->GetActorLocation() - GetActorLocation();
	//AddMovementInput(Direction, 1);

	//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPawn->GetActorLocation());
	//SetActorRotation(Rotation);

}

float AMyCharacter_Zombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurHp <= 0)
	{
		return DamageAmount;
	}

	//데미지 종류에 맞게 데미지 작업
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* Event = (FPointDamageEvent*)(&DamageEvent);
		if (Event)
		{

			CurHp -= DamageAmount;
			UE_LOG(LogTemp, Warning, TEXT("Point Damage : %f %s"), DamageAmount, *(Event->HitInfo.BoneName.ToString()));
			UE_LOG(LogTemp, Warning, TEXT("Point CurHp : %f"), CurHp);

			SpawnHitEffect(Event->HitInfo);
		}
	}
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* Event = (FRadialDamageEvent*)(&DamageEvent);
		if (Event)
		{
			CurHp -= DamageAmount;

			UE_LOG(LogTemp, Warning, TEXT("Radial Damage %f %s"), DamageAmount, *Event->DamageTypeClass->GetName());
		}
	}
	else //(DamageEvent.IsOfType(FDamageEvent::ClassID))
	{
		CurHp -= DamageAmount;
		UE_LOG(LogTemp, Warning, TEXT("Damage : %f"), DamageAmount);
		UE_LOG(LogTemp, Warning, TEXT("CurHp : %f"), CurHp);
	}

	if (CurHp <= 0)
	{
		//Death Montage
		DoDead();
	}

	return 0.0f;

}

void AMyCharacter_Zombie::DoDeadEnd()
{
	//네트워크를 위해 DoDeadEnd와 분리
	TArray<FName> DeathMontageList;
	DeathMontageList.Add(TEXT("Back"));
	DeathMontageList.Add(TEXT("Front"));
	DeathMontageList.Add(TEXT("Front2"));
	DeathMontageList.Add(TEXT("Front3"));
	DeathMontageList.Add(TEXT("Left"));
	DeathMontageList.Add(TEXT("Right"));
	int32 RandDeathListNum = FMath::RandRange(0, DeathMontageList.Num() - 1);

	PlayAnimMontage(DeathMontage, 1.0f, DeathMontageList[RandDeathListNum]);
	UE_LOG(LogTemp, Warning, TEXT("DoDead"));
}

void AMyCharacter_Zombie::DoDead()
{
	UE_LOG(LogTemp, Warning, TEXT("Character_DoDeadEnd"));
	GetController()->SetActorEnableCollision(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMyCharacter_Zombie::SpawnHitEffect(FHitResult Hit)
{
	if (BloodEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			BloodEffect,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation());

	}

}

void AMyCharacter_Zombie::SetState(EZombieState NewState)
{
	CurState = NewState;
}
