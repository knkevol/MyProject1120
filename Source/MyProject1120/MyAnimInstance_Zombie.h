// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacter_Zombie.h"
#include "MyAnimInstance_Zombie.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API UMyAnimInstance_Zombie : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	uint8 bIsDeath : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1127")
	EZombieState CurState;

	
};
