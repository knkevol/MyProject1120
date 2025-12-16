// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ItemBase.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class AProjectileBase;
class UAnimMontage;


UCLASS()
class MYPROJECT1120_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UParticleSystem> MuzzleFlash;

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void FireProjectile(FTransform SpawnTransform, FHitResult InHitResult);

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSubclassOf<AProjectileBase> ProjectileTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName SocketName = TEXT("HandGrip_R");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MaxBullet = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 CurBullet = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<class USoundBase> FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	uint8 bFullAuto : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (ClampMin = 0.1f, ClampMax = 2.0f, Unit = "s"))
	float ReFireRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float TimeofLastShoot = 0.0f;

	FTimerHandle RefireTimer;


	bool CalculateShootData(FVector& OutSpawnLocation, FVector& OutTargetLocation, FRotator& OutAimRotation);

	FVector GetWeaponTargetLocation();

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_SpawnMuzzleFlash(const FVector& OutSpawnLocation, const FRotator& OutAimRotation);
	void S2A_SpawnMuzzleFlash_Implementation(const FVector& OutSpawnLocation, const FRotator& OutAimRotation);

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_SpawnSound(const FVector& OutSpawnLocation);
	void S2A_SpawnSound_Implementation(const FVector& OutSpawnLocation);
};
