// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class EState : uint8
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 10 UMETA(DisplayName = "Pistol"),
	Rifle = 20 UMETA(DisplayName = "Rifle")
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

	UFUNCTION(BlueprintCallable)
	void Move(float InRoll, float InPitch);

	UFUNCTION(BlueprintCallable)
	void Look(float InRoll, float InPitch);

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
	EState State = EState::Unarmed;

};
