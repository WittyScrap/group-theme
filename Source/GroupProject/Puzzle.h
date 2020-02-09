// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

///////////////////////////////
#include "Puzzle.generated.h"//
///////////////////////////////

DECLARE_LOG_CATEGORY_EXTERN(GameLog, Verbose, All);

/**
 * 
 */
UCLASS()
class GROUPPROJECT_API APuzzle : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	// Contains all the game rules that apply overall to the puzzle rooms.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Rules")
	TMap<FName, int> GameRules;

	/*
	 * Sets the value for a game rule as defined within the
	 * game rules dictionary. If a game rule does not exist,
	 * a new one is created with the given ruleName and will
	 * default to the given value.
	 *
	 * @param ruleName The name of the rule to override/create.
	 * @param value The value to assign to the game rule.
	 */
	UFUNCTION(Exec, Category = ExecFunctions)
	void GameRule(const FName& ruleName, const int& value);

public:

	/*
	 * Sets the value for a game rule as defined within the
	 * game rules dictionary. If a game rule does not exist,
	 * a new one is created with the given ruleName and will
	 * default to the given value.
	 *
	 * @param ruleName The name of the rule to override/create.
	 * @param value The value to assign to the game rule.
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void SetRule(const FName& ruleName, const int& value);

	/*
	 * Retrieves the value of a given rule from the game rules
	 * dictionary. If the rule does not exist, the return value
	 * will be set to zero, and false will be returned from this
	 * function.
	 *
	 * @param visible Whether or not the cursor should be visible.
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	const bool GetRule(const FName& ruleName, int& value);
};
