// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYPROJECT1120_API NetworkUtil
{
public:
	NetworkUtil();
	~NetworkUtil();

public:
	static void Log(UWorld* InWorld, const FString& InString);
};
