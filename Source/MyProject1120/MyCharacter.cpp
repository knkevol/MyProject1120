// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ChildActorComponent.h"
#include "EnhancedInputComponent.h"
#include "Weapon/WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/DamageTypeBase.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetArrayLibrary.h"
#include "PickupItemBase.h"
#include "Components/DecalComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));

	SetGenericTeamId(1);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//델리게이트 바인딩
	OnActorBeginOverlap.AddDynamic(this, &AMyCharacter::ProcessBeginOverlap);

	
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Reload, ETriggerEvent::Completed, this, &AMyCharacter::Reload);
		UIC->BindAction(IA_Fire, ETriggerEvent::Started, this, &AMyCharacter::StartFire);
		UIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &AMyCharacter::StopFire);
		UIC->BindAction(IA_Zoom, ETriggerEvent::Started, this, &AMyCharacter::StartZoom);
		UIC->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &AMyCharacter::StopZoom);
	}

}

void AMyCharacter::Move(float InRoll, float InPitch)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, GetControlRotation().Roll)), InRoll);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), InPitch);
	
}

void AMyCharacter::Look(float InRoll, float InPitch)
{
	AddControllerYawInput(InRoll);
	AddControllerPitchInput(InPitch);

	//CanCrouch();
}

void AMyCharacter::Reload()
{
	//PlayAnimMontage;
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		PlayAnimMontage(ChildWeapon->ReloadMontage);
	}
}

void AMyCharacter::HitReact()
{
	//FString SectionName = FString::Printf(TEXT("%d"), FMath::RandRange(1, 8));
	//PlayAnimMontage(HitMontage, 1.0, FName(*SectionName));
}

void AMyCharacter::ReloadWeapon()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Reload();
	}
}

void AMyCharacter::DoFire()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::DoFire()"));
		PlayAnimMontage(ChildWeapon->FireMontage);
		ChildWeapon->Fire();
	}
}

void AMyCharacter::StartFire()
{
	bIsFire = true;
	DoFire();
}

void AMyCharacter::StopFire()
{
	bIsFire = false;
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->StopFire();
	}

}

void AMyCharacter::DoDeadEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Character_DoDeadEnd"));
	GetController()->SetActorEnableCollision(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMyCharacter::DoDead()
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

void AMyCharacter::DoHit()
{
	TArray<FName> HitMontageList;
	HitMontageList.Add(TEXT("BackMed"));
	HitMontageList.Add(TEXT("FrontHvy"));
	HitMontageList.Add(TEXT("FrontLgt"));
	HitMontageList.Add(TEXT("FrontLgt2"));
	HitMontageList.Add(TEXT("FrontLgt3"));
	HitMontageList.Add(TEXT("FrontLgt4"));
	HitMontageList.Add(TEXT("FrontMed"));
	HitMontageList.Add(TEXT("FrontMed2"));
	int32 RandHitListNum = FMath::RandRange(0, HitMontageList.Num() - 1);

	PlayAnimMontage(HitMontage, 1.0f, HitMontageList[RandHitListNum]);
}

void AMyCharacter::StartZoom()
{
	bIsZoom = true;
}

void AMyCharacter::StopZoom()
{
	bIsZoom = false;
}


void AMyCharacter::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APickupItemBase* PickedItem = Cast<APickupItemBase>(OtherActor);
	if (PickedItem)
	{
		//FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this;
		//SpawnParams.Instigator = this;
		//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		switch (PickedItem->ItemType)
		{
		case EItemType::Use:
			UseItem(PickedItem);
			break;
		case EItemType::Eat:
			EatItem(PickedItem);
			break;
		case EItemType::Equip:
			EquipItem(PickedItem);
			break;
		}

		if (!PickedItem->bIsInfinity)
		{
			PickedItem->Destroy();
		}
		

		
	}
}

void AMyCharacter::EquipItem(APickupItemBase* PickedItem)
{
	Weapon->SetChildActorClass(PickedItem->ItemTemplate);
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	//장착하는 아이템인지 예외처리 필요
	if (ChildWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::EquipItem"));
		if (ChildWeapon->Name.Compare(TEXT("Pistol")) == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::EquipItem_Pistol"));
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			State = EState::Pistol;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon->Name.Compare(TEXT("Rifle")) == 0)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			State = EState::Rifle;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon->Name.Compare(TEXT("Launcher")) == 0)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			State = EState::Launcher;
			ChildWeapon->SetOwner(this);
		}
		
	}
}

void AMyCharacter::UseItem(APickupItemBase* PickedItem)
{
	//Weapon->SetChildActorClass(PickedItem->ItemTemplate);
	//AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	////장착하는 아이템인지 예외처리 필요
	//if (ChildWeapon)
	//{
	//	ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
	//	State = EState::Pistol;
	//	//State = EState::Rifle;
	//	//State = EState::Launcher;
	//	ChildWeapon->SetOwner(this);
	//}
}

void AMyCharacter::EatItem(APickupItemBase* PickedItem)
{
	//Weapon->SetChildActorClass(PickedItem->ItemTemplate);
	//AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	////장착하는 아이템인지 예외처리 필요
	//if (ChildWeapon)
	//{
	//	ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
	//	State = EState::Pistol;
	//	//State = EState::Rifle;
	//	//State = EState::Launcher;
	//	ChildWeapon->SetOwner(this);
	//}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
	DoHit();

	if (CurHp <= 0)
	{
		//Death Montage
		DoDead();
	}


	return 0.0f;
}

void AMyCharacter::SpawnHitEffect(FHitResult Hit)
{
	if (BloodEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			BloodEffect,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation());

	}
	
}

void AMyCharacter::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId AMyCharacter::GetGenericTeamId() const
{
	
	return TeamID;
}
