// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class APickupItemBase;
class UAIPerceptionStimuliSourceComponent;

UENUM(BlueprintType)
enum class EState : uint8
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 10 UMETA(DisplayName = "Pistol"),
	Rifle = 20 UMETA(DisplayName = "Rifle"),
	Launcher = 30 UMETA(DisplayName = "Launcher")
};

UCLASS()
class MYPROJECT1120_API AMyCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "1120")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "1120")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	TObjectPtr<class UChildActorComponent> Weapon;


	// -----Input Function-----
	UFUNCTION(BlueprintCallable)
	void Move(float InRoll, float InPitch);

	UFUNCTION(BlueprintCallable)
	void Look(float InRoll, float InPitch);

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void HitReact();

	UFUNCTION(BlueprintCallable)
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable)
	void DoFire(/*const FInputActionValue& Value*/);

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void DoDeadEnd();

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(BlueprintCallable)
	void DoHit();

	UFUNCTION(BlueprintCallable)
	void StartZoom();

	UFUNCTION(BlueprintCallable)
	void StopZoom();
	// -------------------------


	void EquipItem(APickupItemBase* PickedItem);

	void UseItem(APickupItemBase* PickedItem);

	void EatItem(APickupItemBase* PickedItem);

	

	// -----Server-----
	void StartRun();
	void StopRun();

	void StartLeanL();
	void StopLeanL();
	void StartLeanR();
	void StopLeanR();

	void StartCrouch();
	void StopCrouch();

	void DoReload();

	//UFUNCTION(목적지, 값보장)
	UFUNCTION(Server, Reliable)
	void C2S_StartRun();
	void C2S_StartRun_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_StopRun();
	void C2S_StopRun_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_StartZoom();
	void C2S_StartZoom_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_StopZoom();
	void C2S_StopZoom_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_StartFire();
	void C2S_StartFire_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_StopFire();
	void C2S_StopFire_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_Reload();
	void C2S_Reload_Implementation();

	UFUNCTION(Server, Reliable)
	void C2S_Death();
	void C2S_Death_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_HitEffect(const FHitResult& Hit);
	void S2A_HitEffect_Implementation(const FHitResult& Hit);

	//UFUNCTION(Server, Reliable)
	//void C2S_StartLeanL();
	//void C2S_StartLeanL_Implementation();

	//UFUNCTION(Server, Reliable)
	//void C2S_StopLeanL();
	//void C2S_StopLeanL_Implementation();

	//UFUNCTION(Server, Reliable)
	//void C2S_StartLeanR();
	//void C2S_StartLeanR_Implementation();

	//UFUNCTION(Server, Reliable)
	//void C2S_StopLeanR();
	//void C2S_StopLeanR_Implementation();

	//UFUNCTION(Server, Reliable)
	//void C2S_StartCrouch();
	//void C2S_StartCrouch_Implementation();

	//UFUNCTION(Server, Reliable)
	//void C2S_StopCrouch();
	//void C2S_StopCrouch_Implementation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// -----------------



	// -----Delegate-----
	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

		

	// -----Input Variable-----
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bSprint : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bLeanL : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bLeanR : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bAiming : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bCrouch : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bIsZoom : 1 = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	uint8 bIsFire : 1 = false;


	// -----Player State-----
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	float CurHp = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	float MaxHp = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1205", Replicated)
	EState State = EState::Unarmed;


	// -----Montage-----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1208", Replicated)
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1208", Replicated)
	TObjectPtr<UAnimMontage> DeathMontage;

	// -----Effect-----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1208", Replicated)
	TObjectPtr<UParticleSystem> BloodEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1128")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnHitEffect(FHitResult Hit);


	// -----Input Action-----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UInputAction> IA_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UInputAction> IA_Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1205")
	TObjectPtr<UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1205")
	TObjectPtr<UInputAction> IA_LeanL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1205")
	TObjectPtr<UInputAction> IA_LeanR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1205")
	TObjectPtr<UInputAction> IA_Crouch;

	// ----IGenericTeamAgentInterface-----
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	FGenericTeamId TeamID;

	void DrawFrustum();


	FRotator GetAimOffset() const;
};
