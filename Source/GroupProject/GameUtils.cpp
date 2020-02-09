// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"


// Prints to the console and the screen.
void UGameUtils::Print(FString text, bool log, FColor color, float time)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, time, color, text);
	}

	if (log)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	}
}

// Inverts a vector.
void UGameUtils::NegateVector(FVector& inOutVector)
{
	inOutVector.X *= -1;
	inOutVector.Y *= -1;
	inOutVector.Z *= -1;
}

// Multiplies a vector by a value.
void UGameUtils::MultiplyVector(FVector& inOutVector, const float& value)
{
	inOutVector.X *= value;
	inOutVector.Y *= value;
	inOutVector.Z *= value;
}
