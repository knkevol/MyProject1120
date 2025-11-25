// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DamageTypeBase.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Reload()
{
	CurBullet = MaxBullet;
	UE_LOG(LogTemp, Warning, TEXT("Reload %d"), CurBullet);
}

void AWeaponBase::Fire()
{
	float CurrentTimeofShoot = GetWorld()->TimeSeconds - TimeofLastShoot;

	if (CurrentTimeofShoot > ReFireRate)
	{
		return;
	}

	if (bFullAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(ReFireTimer, this, &AWeaponBase::Fire, ReFireRate, false);
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	ensure(Character);

	APlayerController* PC = Cast<APlayerController>(Character->GetController());
	if (PC)
	{

	}

	CurBullet--;
	UE_LOG(LogTemp, Warning, TEXT("Fire %d"), CurBullet);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, GetActorLocation());

	
	TimeofLastShoot = GetWorld()->TimeSeconds;
}

void AWeaponBase::StopFire()
{
	//GetWorld()->
}

void AWeaponBase::FireProjectile()
{
}

