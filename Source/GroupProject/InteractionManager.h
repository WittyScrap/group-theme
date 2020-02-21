// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include <list>

#include "InteractionManager.generated.h"

class AInteractionReceiver;

/**
 * 
 */
UCLASS()
class GROUPPROJECT_API AInteractionManager : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	TMap<int32, std::list<AInteractionReceiver*>> Targets;

public:
	void Register(AInteractionReceiver* target);
	UFUNCTION(BlueprintCallable, Category = Interaction) void Broadcast(const int& requestID, bool stateID);
};
