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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1120")
	float Direction;

	UFUNCTION()
	void AnimNotify_SkeletonNotify();
	
};
