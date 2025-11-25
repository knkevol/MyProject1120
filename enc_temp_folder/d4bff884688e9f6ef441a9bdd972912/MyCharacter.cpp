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

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//무기 집으면 잡게 이동
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
		State = EState::Pistol;
	}
	
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
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyCharacter::DoFire);
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
	//AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	//if (ChildWeapon)
	//{
	//	ChildWeapon->Fire();
	//}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		//PC->DeprojectMousePositionToWorld()
		int32 SizeX = 0;
		int32 SizeY = 0;
		int32 CenterX = 0;
		int32 CenterY = 0;
		FVector WorldDirection;
		FVector WorldLocation;
		FVector CameraLocation;
		FRotator CameraRotation;
		
		PC->GetViewportSize(SizeX, SizeY);
		CenterX = SizeX / 2;
		CenterY = SizeY / 2;

		
		PC->DeprojectScreenPositionToWorld((float)CenterX, (float)CenterY, WorldLocation, WorldDirection);
		PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector Start = CameraLocation;
		FVector End = CameraLocation + (WorldDirection * 100000.0f);
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
		
		
		TArray<AActor*> IgnoreActors;
		//해당작업 마지막 인자로 구현가능
		//IgnoreActors.Add(this);

		FHitResult HitResult;

		bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			Start,
			End,
			ObjectTypes,
			true,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true
		);
		if (bResult)
		{
			//RPG
			//UGameplayStatics::ApplyDamage(HitResult.GetActor(), 50, GetController(), this, UDamageTypeBase::StaticClass());
			//총
			UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), 10, -HitResult.ImpactNormal, HitResult, GetController(), this, UDamageTypeBase::StaticClass());
			//범위, 수류탄
			//UGameplayStatics::ApplyRadialDamage(HitResult.GetActor(),50, HitResult.ImpactPoint, 300.0f, UDamageTypeBase::StaticClass(), IgnoreActors,	this, GetController(), true);
			UE_LOG(LogTemp, Warning, TEXT("HitObject : %s"), *HitResult.GetActor()->GetName());
		}
	}


}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

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
	
	TArray<FName> DeathMontageList;
	DeathMontageList.Add(TEXT("Back"));
	DeathMontageList.Add(TEXT("Front"));
	DeathMontageList.Add(TEXT("Front2"));
	DeathMontageList.Add(TEXT("Front3"));
	DeathMontageList.Add(TEXT("Left"));
	DeathMontageList.Add(TEXT("Right"));
	int32 RandDeathListNum = FMath::RandRange(0, DeathMontageList.Num() - 1);


	//데미지 종류에 맞게 데미지 작업
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* Event = (FPointDamageEvent*)(&DamageEvent);
		if (Event)
		{
			CurHp -= DamageAmount;
			PlayAnimMontage(HitMontage, 1.0f, HitMontageList[RandHitListNum]);
			UE_LOG(LogTemp, Warning, TEXT("Point Damage : %f %s"), DamageAmount, *(Event->HitInfo.BoneName.ToString()));
			UE_LOG(LogTemp, Warning, TEXT("Point CurHp : %f"), CurHp);
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
		PlayAnimMontage(DeathMontage, 1.0f, DeathMontageList[RandDeathListNum]);
		GetMesh()->SetSimulatePhysics(true);
	}


	return 0.0f;
}
