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
#include "ProjectileBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "../MyProject1120.h"
#include "../Network/NetworkUtil.h"
#include "../MyCharacter.h"
#include "Camera/CameraComponent.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		NET_LOG(FString::Printf(TEXT("Weapon Owver %s"), *GetOwner()->GetName()));
	}
	else
	{
		NET_LOG(FString::Printf(TEXT("No Owver")));
	}
	
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

	if (CurrentTimeofShoot < ReFireRate)
	{
		return;
	}

	if (bFullAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(RefireTimer, this, &AWeaponBase::Fire, ReFireRate, false);
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	ensure(Character);
	if (!Character)
	{
		return;
	}
	//Calculate
	FVector SpawnLocation;
	FVector TargetLocation;
	//FVector BulletDirection;
	FRotator AimRotation;
	FHitResult HitResult;

	//SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle"));
	//FVector WeaponForward = Mesh->GetSocketRotation(TEXT("Muzzle")).Vector().GetSafeNormal();
	//TargetLocation = SpawnLocation + (WeaponForward * 100000.0f);
	//AimRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, TargetLocation + (UKismetMathLibrary::RandomUnitVector() * 0.3));

	bool bResult = CalculateShootData(SpawnLocation, TargetLocation, AimRotation);
	if (!bResult)
	{
		return;
	}


	FireProjectile(FTransform(AimRotation, SpawnLocation, FVector::OneVector), HitResult);

	//Call = Server. 실행 = Client
	S2A_SpawnMuzzleFlash(SpawnLocation, AimRotation);
	S2A_SpawnSound(SpawnLocation);
	// Recoil
	Character->AddControllerPitchInput(-0.5f);

	CurBullet--;
	UE_LOG(LogTemp, Warning, TEXT("Fire %d"), CurBullet);
	TimeofLastShoot = GetWorld()->TimeSeconds;
}

void AWeaponBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(RefireTimer);
}

void AWeaponBase::FireProjectile(FTransform SpawnTransform, FHitResult InHitResult)
{

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileTemplate, SpawnTransform);
	Projectile->HitResult = InHitResult;
	Projectile->SetOwner(this);
	
}

bool AWeaponBase::CalculateShootData(FVector& OutSpawnLocation, FVector& OutTargetLocation, FRotator& OutAimRotation)
{

	AMyCharacter* Character = Cast<AMyCharacter>(GetOwner());
	if (!Character)
	{
		return false;
	}

	FHitResult OutHit;

	const FVector Start = Character->GetCameraComponent()->GetComponentLocation();
	const FVector End = Start + (Character->GetCameraComponent()->GetForwardVector() * 10000.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(Character);

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, QueryParams);

	//Calculate
	OutSpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle"));
	OutTargetLocation = OutHit.bBlockingHit ? OutHit.ImpactPoint : OutHit.TraceEnd;


	OutAimRotation = UKismetMathLibrary::FindLookAtRotation(OutSpawnLocation, OutTargetLocation + (UKismetMathLibrary::RandomUnitVector() * 0.3));


	return true;
}

FVector AWeaponBase::GetWeaponTargetLocation()
{
	AMyCharacter* Character = Cast<AMyCharacter>(GetOwner());

	if (!Character)
	{
		return FVector::Zero();
	}

	FHitResult OutHit;

	const FVector Start = Character->GetCameraComponent()->GetComponentLocation();
	const FVector End = Start + (Character->GetCameraComponent()->GetForwardVector() * 10000.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, QueryParams);

	// return either the impact point or the trace end
	return OutHit.bBlockingHit ? OutHit.ImpactPoint : OutHit.TraceEnd;
}

// Client에서만 실행. Server to All
void AWeaponBase::S2A_SpawnMuzzleFlash_Implementation(const FVector& OutSpawnLocation, const FRotator& OutAimRotation)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, OutSpawnLocation, OutAimRotation);
}

void AWeaponBase::S2A_SpawnSound_Implementation(const FVector& OutSpawnLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("S2A_SpawnSound_Implementation"));
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, OutSpawnLocation);
}

