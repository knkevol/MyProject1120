// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(10, 10, 5));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->MaxSpeed = 8000.0f;
	Movement->InitialSpeed = 8000.f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AProjectileBase::ProcessBeginOverlap);
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(5, 5, 5), 
		HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), 5.f);

	//MadeDecal->SetFadeScreenSize(0.005f);
	
	//RPG 
			//UGameplayStatics::ApplyDamage(HitResult.GetActor(),
			//	50,
			//	PC,
			//	this,
			//	UDamageTypeBase::StaticClass()
			//);

			//ÃÑ½î´Â µ¥¹ÌÁö
	//UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),
	//	10,
	//	-HitResult.ImpactNormal,
	//	HitResult,
	//	PC,
	//	this,
	//	UDamageTypeBase::StaticClass()
	//);

	////¹üÀ§ °ø°Ý, ÆøÅº
	//UGameplayStatics::ApplyRadialDamage(HitResult.GetActor(),
	//	10,
	//	HitResult.ImpactPoint,
	//	300.0f,
	//	UDamageTypeBase::StaticClass(),
	//	IngnoreActors,
	//	this,
	//	PC,
	//	true
	//);
}