// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObject.h"

// Sets default values
AMovableObject::AMovableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called every frame
void AMovableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Whether or not this object is being held.
const bool AMovableObject::IsHeld() const
{
	return Holder != nullptr;
}

// The object holder.
ASuicidalController* AMovableObject::GetHolder() const
{
	return Holder;
}

// Picks up this object.
void AMovableObject::PickUp(ASuicidalController* const holderActor)
{
	if (holderActor)
	{
		Holder = holderActor;
		OnPickedUp(Holder);
	}
}

// Drops this object.
void AMovableObject::Drop()
{
	Holder = nullptr;
	OnDropped();
}

