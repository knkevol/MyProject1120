// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Reload.h"

FString UAnimNotify_Reload::GetNotifyName_Implementation() const
{
	return FString();
}

void UAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}
