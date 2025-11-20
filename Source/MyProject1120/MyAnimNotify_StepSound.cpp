// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify_StepSound.h"

void UMyAnimNotify_StepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

}

FString UMyAnimNotify_StepSound::GetNotifyName_Implementation() const
{
	return TEXT("StepSound");
}