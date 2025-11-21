// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void AnimNotify_SkeletonNotify();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float AimYaw;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float AimPitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bLeanL : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bLeanR : 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	uint8 bAiming : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float CurrentLeanAngle;

	
	
};
