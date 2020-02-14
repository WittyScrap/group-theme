// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionReceiver.h"

AInteractionReceiver::AInteractionReceiver()
{
	PrimaryActorTick.bCanEverTick = false;
}

const int32& AInteractionReceiver::GetID() const
{
	return ReceiverID;
}

void AInteractionReceiver::Set(bool state)
{
	if (state)
	{
		OnSet();
	}
	else
	{
		OnUnset();
	}
}

void AInteractionReceiver::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();

	if (world)
	{
		AInteractionManager* manager = Cast<AInteractionManager>(world->GetGameState());

		if (manager)
		{
			manager->Register(this);
		}
	}
}

