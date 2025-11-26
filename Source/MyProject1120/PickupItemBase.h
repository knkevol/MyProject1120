// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Use = 0 UMETA(DisplayName = "Use"),
	Eat= 10 UMETA(DisplayName = "Eat"),
	Equip = 20 UMETA(DisplayName = "Equip")
};

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class MYPROJECT1120_API APickupItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "1126")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "1126")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1126")
	EItemType ItemType = EItemType::Equip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "1126")
	TSubclassOf<class AItemBase> ItemTemplate;

};
