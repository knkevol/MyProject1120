// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "PCMBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT1120_API APCMBase : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	APCMBase();

	virtual void UpdateCamera(float DeltaTime) override;
	
};
