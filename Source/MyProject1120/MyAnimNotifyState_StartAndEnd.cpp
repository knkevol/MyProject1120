// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState_StartAndEnd.h"

FString UMyAnimNotifyState_StartAndEnd::GetNotifyName_Implementation() const
{
	return FString(TEXT("StartAndEnd"));
}

void UMyAnimNotifyState_StartAndEnd::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	UE_LOG(LogTemp, Warning, TEXT("NotifyBegin"));
}

void UMyAnimNotifyState_StartAndEnd::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("NotifyTick"));
}

void UMyAnimNotifyState_StartAndEnd::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	UE_LOG(LogTemp, Warning, TEXT("NotifyEnd"));
}
