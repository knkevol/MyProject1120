// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class APickupItemBase;

UENUM(BlueprintType)
enum class EState : uint8
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 10 UMETA(DisplayName = "Pistol"),
	Rifle = 20 UMETA(DisplayName = "Rifle"),
	Launcher = 30 UMETA(DisplayName = "Launcher")
};

UCLASS()
class MYPROJECT1120_API AMyCharacter : public ACharacter
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

	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void EquipItem(APickupItemBase* PickedItem);

	void UseItem(APickupItemBase* PickedItem);

	void EatItem(APickupItemBase* PickedItem);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnHitEffect(FHitResult Hit);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bSpirnt : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bLeanL : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bLeanR : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bAiming : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bCrouch : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bIsZoom : 1 = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float CurHp = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float MaxHp = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bIsFire : 1 = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	EState State = EState::Unarmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UInputAction> IA_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1120")
	TObjectPtr<UInputAction> IA_Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1127")
	TObjectPtr<UParticleSystem> BloodEffect;


};
