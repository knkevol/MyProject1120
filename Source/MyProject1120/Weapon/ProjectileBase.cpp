// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "DamageTypeBase.h"
#include "../Network/NetworkUtil.h"


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

	bReplicates = true;
	SetReplicateMovement(true);
	bNetLoadOnClient = true;
	bNetUseOwnerRelevancy = true;


}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//OnActorBeginOverlap.AddDynamic(this, &AProjectileBase::ProcessBeginOverlap);
	Box->OnComponentHit.AddDynamic(this, &AProjectileBase::ProcessComponentHit);

	//설정 안해주면 액터 누수로 네트워크 느려져서 정상작동 안됨
	SetLifeSpan(5.0f);
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(15, 15, 15),
		HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), 5.f);

	MadeDecal->SetFadeScreenSize(0.005f);
	
	//RPG 
			//UGameplayStatics::ApplyDamage(HitResult.GetActor(),
			//	50,
			//	PC,
			//	this,
			//	UDamageTypeBase::StaticClass()
			//);

			

	////범위 공격, 폭탄
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

void AProjectileBase::ProcessComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	SpawnHitEffect(Hit);

	////Owner 확인
	//if (GetOwner())
	//{
	//	NET_LOG(FString::Printf(TEXT("Bullet Owner : %s"), *GetOwner()->GetName()));
	//}
	//else
	//{
	//	NET_LOG(TEXT("NoOwner"));
	//}

	if (!HasAuthority())
	{
		//서버아니면 총알주인 없음
		return;
	}

	//클라이언트는 복제된 것이기 떄문에 Owner가 없음. 소유권 없이 따라감. hit됐을때 Owner가 없기떄문에 프로그램이 죽는다.
	APawn* Pawn = Cast<APawn>(GetOwner()->GetOwner());
	if (Pawn)
	{
		//NET_LOG(FString::Printf(TEXT("%s %s"), *OtherActor->GetName(), *OtherComp->GetName()));
		//총 데미지
		UGameplayStatics::ApplyPointDamage(Hit.GetActor(),
			Damage,
			-Hit.ImpactNormal,
			Hit,
			Pawn->GetController(),
			this,
			UDamageTypeBase::StaticClass());
	}
}

void AProjectileBase::SpawnHitEffect(FHitResult Hit)
{
	if (Decal)
	{
		UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(5, 5, 5),
			Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), 5.f);

		if (MadeDecal)
		{
			MadeDecal->SetFadeScreenSize(0.005f);
		}
		
	}
}
