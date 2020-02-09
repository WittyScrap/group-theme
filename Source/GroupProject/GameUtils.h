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
	/*
	 * Print:
	 * Allows for a log message to be printed to either the log
	 * console or the screen.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static void Print(FString text, bool log = false, FColor color = FColor::Green, float time = 1.f);

	/*
	 * NegateVector:
	 * Negates all components of the input vector.
	 * This method does not create a new instance of a vector, and
	 * instead reuses the same instance.
	 *
	 * @param inOutVector The vector to negate.
	 */
	static void NegateVector(FVector& inOutVector);

	/*
	 * MultiplyVector:
	 * Multiplies all components of a vector by a value.
	 * This method does not create a new instance of a vector, and
	 * instead reuses the same instance.
	 *
	 * @param inOutVector The vector to multiply.
	 * @param value The amount to multiply the vector by.
	 */
	static void MultiplyVector(FVector& inOutVector, const float& value);
};