// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"


/**
 * Print:
 * Allows for a log message to be printed to either the log
 * console or the screen.
 *
 */
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