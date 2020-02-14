// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "InteractionManager.h"

#include "InteractionReceiver.generated.h"

UCLASS()
class GROUPPROJECT_API AInteractionReceiver : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Receiver: Properties") int32 ReceiverID;

public:	
	// Sets default values for this actor's properties
	AInteractionReceiver();
	const int32& GetID() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Receiver: Events") void OnSet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Receiver: Events") void OnUnset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


};
