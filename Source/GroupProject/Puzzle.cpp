// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"

DEFINE_LOG_CATEGORY(GameLog);

// Sets an in-game rule.
void APuzzle::GameRule(const FName& ruleName, const int& value)
{
	SetRule(ruleName, value);

	UE_LOG(GameLog, Log, TEXT("Set rule \"%s\" to value: %d"), *ruleName.ToString(), value);
}

// Sets an in-game rule.
void APuzzle::SetRule(const FName& ruleName, const int& value)
{
	if (GameRules.Contains(ruleName))
	{
		GameRules[ruleName] = value;
	}
	else
	{
		GameRules.Add(ruleName, value);
	}
}

// Tries getting a rule from the rule set.
const bool APuzzle::GetRule(const FName& ruleName, int& value)
{
	int* rule = GameRules.Find(ruleName);

	if (rule)
	{
		value = *rule;
		return true;
	}

	value = 0;
	return false;
}
