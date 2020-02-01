// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

///////////////////////////////////////////
#include "GameUtils.generated.h" //////////
///////////////////////////////////////////

/**
 * 
 */
UCLASS()
class GROUPPROJECT_API UGameUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Print:
	 * Allows for a log message to be printed to either the log
	 * console or the screen.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static void Print(FString text, bool log = false, FColor color = FColor::Green, float time = 1.f);
};