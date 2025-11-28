// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter_Zombie.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	Normal = 0 UMETA(DisplayName = "Narmal"),
	Chase = 5 UMETA(DisplayName = "Chase"),
	Battle = 10 UMETA(DisplayName = "Battle"),
	Death = 15 UMETA(DisplayName = "Death")
};

UCLASS()
class MYPROJECT1120_API AMyCharacter_Zombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter_Zombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void DoDeadEnd();

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(BlueprintCallable)
	virtual void SpawnHitEffect(FHitResult Hit);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	EZombieState CurState;

	void SetState(EZombieState NewState);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	float CurHp = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	float MaxHp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1127")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1127")
	TObjectPtr<UParticleSystem> BloodEffect;

	UFUNCTION(BlueprintCallable)
	void ChangeSpeed(float NewMaxSpeed);

	FORCEINLINE const EZombieState GetCurrentState() { return CurState; }

};
