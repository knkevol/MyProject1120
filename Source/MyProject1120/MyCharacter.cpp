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
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


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

	//DrawFrustum();

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
		UIC->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &AMyCharacter::StartZoom);
		UIC->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &AMyCharacter::StopZoom);
		UIC->BindAction(IA_Run, ETriggerEvent::Triggered, this, &AMyCharacter::StartRun);
		UIC->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
		UIC->BindAction(IA_LeanL, ETriggerEvent::Triggered, this, &AMyCharacter::StartLeanL);
		UIC->BindAction(IA_LeanL, ETriggerEvent::Completed, this, &AMyCharacter::StopLeanL);
		UIC->BindAction(IA_LeanR, ETriggerEvent::Triggered, this, &AMyCharacter::StartLeanR);
		UIC->BindAction(IA_LeanR, ETriggerEvent::Completed, this, &AMyCharacter::StopLeanR);
		UIC->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AMyCharacter::StartCrouch);
		UIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AMyCharacter::StopCrouch);
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
	//bAiming = true;
	C2S_StartZoom();
}

void AMyCharacter::StopZoom()
{
	bIsZoom = false;
	//bAiming = false;
	C2S_StopZoom();
}


void AMyCharacter::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//Client는 무기 X
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !PC->HasAuthority())
	{
		return;
		/*if (PC->GetNetMode() == ENetMode::NM_Client)
		{
			return;
		}*/
	}

	APickupItemBase* PickedItem = Cast<APickupItemBase>(OtherActor);
	if (PickedItem)
	{
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

		//Client일때도 소유권
		PickedItem->SetOwner(this);

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
		if (ChildWeapon->Name.Compare(TEXT("Pistol")) == 0)
		{
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

void AMyCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	C2S_StartRun();
}

void AMyCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	C2S_StopRun();
}

void AMyCharacter::StartLeanL()
{
	bLeanL = true;
}

void AMyCharacter::StopLeanL()
{
	bLeanL = false;
}

void AMyCharacter::StartLeanR()
{
	bLeanR = true;
}

void AMyCharacter::StopLeanR()
{
	bLeanR = false;
}

void AMyCharacter::StartCrouch()
{
	bCrouch = true;
}

void AMyCharacter::StopCrouch()
{
	bCrouch = false;
}

void AMyCharacter::C2S_StartRun_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMyCharacter::C2S_StopRun_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AMyCharacter::C2S_StartZoom_Implementation()
{
	bIsZoom = true;
}

void AMyCharacter::C2S_StopZoom_Implementation()
{
	bIsZoom = false;
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

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, bSprint);
	DOREPLIFETIME(AMyCharacter, bLeanL);
	DOREPLIFETIME(AMyCharacter, bLeanR);
	DOREPLIFETIME(AMyCharacter, bAiming);
	DOREPLIFETIME(AMyCharacter, bCrouch);
	DOREPLIFETIME(AMyCharacter, bIsZoom);
	DOREPLIFETIME(AMyCharacter, bIsFire);
	DOREPLIFETIME(AMyCharacter, CurHp);
	DOREPLIFETIME(AMyCharacter, MaxHp);
	DOREPLIFETIME(AMyCharacter, State);
}

void AMyCharacter::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId AMyCharacter::GetGenericTeamId() const
{
	
	return TeamID;
}

void AMyCharacter::DrawFrustum()
{
	FMinimalViewInfo CameraView;
	// 카메라의 현재 뷰 정보(위치, 회전, FOV, AspectRatio 등)를 가져옵니다.
	Camera->GetCameraView(0.0f, CameraView);

	// 1. 필요한 투영 매개변수 정의

	// FOV를 라디안으로 변환 (절반 각도)
	const float HalfFOVRadians = FMath::DegreesToRadians(CameraView.FOV / 2.0f);
	const float AspectRatio = CameraView.AspectRatio;

	// Near/Far Clip Distance 정의 (원근 절두체에 필수)
	// 실제 카메라 컴포넌트 설정을 반영하여 값을 정해야 합니다.
	const float NearClipDistance = 10.0f;  // 카메라 앞 10cm (Near Plane)
	const float FarClipDistance = 1000.0f; // 10미터 (Far Plane)

	// 2. Near/Far Plane의 Half Height/Width 계산 (삼각법 사용)

	// H = D * tan(HalfFOV)
	const float HalfHeightNear = NearClipDistance * FMath::Tan(HalfFOVRadians);
	// W = H * AspectRatio
	const float HalfWidthNear = HalfHeightNear * AspectRatio;

	const float HalfHeightFar = FarClipDistance * FMath::Tan(HalfFOVRadians);
	const float HalfWidthFar = HalfHeightFar * AspectRatio;

	// 3. Frustum의 8개 꼭짓점을 로컬 공간에서 계산
	// 카메라 로컬 좌표계: +X = Forward, +Y = Right, +Z = Up
	FVector Corners[8]; // 0~3: Near Plane, 4~7: Far Plane

	// Near Plane (Z=Up/Down, Y=Right/Left)
	Corners[0] = FVector(NearClipDistance, -HalfWidthNear, HalfHeightNear);  // Near Top-Left
	Corners[1] = FVector(NearClipDistance, HalfWidthNear, HalfHeightNear);   // Near Top-Right
	Corners[2] = FVector(NearClipDistance, HalfWidthNear, -HalfHeightNear);  // Near Bottom-Right
	Corners[3] = FVector(NearClipDistance, -HalfWidthNear, -HalfHeightNear); // Near Bottom-Left

	// Far Plane
	Corners[4] = FVector(FarClipDistance, -HalfWidthFar, HalfHeightFar);   // Far Top-Left
	Corners[5] = FVector(FarClipDistance, HalfWidthFar, HalfHeightFar);    // Far Top-Right
	Corners[6] = FVector(FarClipDistance, HalfWidthFar, -HalfHeightFar);   // Far Bottom-Right
	Corners[7] = FVector(FarClipDistance, -HalfWidthFar, -HalfHeightFar);  // Far Bottom-Left

	// 4. 로컬 좌표를 월드 좌표로 변환
	FTransform CameraTransform(CameraView.Rotation, CameraView.Location, FVector(1.0f));
	FVector WorldCorners[8];
	for (int32 i = 0; i < 8; ++i)
	{
		WorldCorners[i] = CameraTransform.TransformPosition(Corners[i]);
	}

	// 5. DebugDrawLine을 사용하여 절두체의 12개 모서리 그리기
	const float LineDuration = 0.0f; // 한 프레임만 표시
	const float LineThickness = 3.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	// Near Plane (앞면) 그리기 (4개 선)
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[0], WorldCorners[1], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[1], WorldCorners[2], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[2], WorldCorners[3], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[3], WorldCorners[0], LineColor, LineDuration, LineThickness);

	// Far Plane (뒷면) 그리기 (4개 선)
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[4], WorldCorners[5], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[5], WorldCorners[6], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[6], WorldCorners[7], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[7], WorldCorners[4], LineColor, LineDuration, LineThickness);

	// 두 평면 연결 (4개 선)
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[0], WorldCorners[4], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[1], WorldCorners[5], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[2], WorldCorners[6], LineColor, LineDuration, LineThickness);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), WorldCorners[3], WorldCorners[7], LineColor, LineDuration, LineThickness);
}

FRotator AMyCharacter::GetAimOffset() const
{
	// World를 받아와서
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	// Local 방향으로 변경
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);

	// 방향벡터
	const FRotator AimRotLS = AimDirLS.Rotation();
	return AimRotLS;
}
