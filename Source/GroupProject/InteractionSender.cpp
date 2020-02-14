// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSender.h"
#include "InteractionManager.h"
#include "Engine/World.h"

// Sets default values
AInteractionSender::AInteractionSender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractionSender::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractionSender::InternalSetTriggers(const int32& id, bool value) const
{
	UWorld* world = GetWorld();

	if (world)
	{
		AInteractionManager* manager = Cast<AInteractionManager>(world->GetGameState());

		if (manager)
		{
			manager->Broadcast(id, value);
		}
	}
}

// Called every frame
void AInteractionSender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionSender::SetTriggers(const int32& triggerID)
{
	InternalSetTriggers(triggerID, true);
}

void AInteractionSender::UnsetTriggers(const int32& triggerID)
{
	InternalSetTriggers(triggerID, false);
}