// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObject.h"

// Sets default values
AMovableObject::AMovableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
	Constraint->SetupAttachment(RootComponent);

	Graphics = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Graphics"));
	Graphics->SetupAttachment(Constraint);
}

// Set up initial paramaters.
void AMovableObject::BeginPlay()
{
	Graphics->SetSimulatePhysics(bShouldSimulatePhysics);
	Constraint->ConstraintActor1 = this;
	Constraint->ComponentName1.ComponentName = *Graphics->GetName();
	
	// Set linear limits...
	Constraint->SetLinearXLimit(GetLinearConstraint(), 0.f);
	Constraint->SetLinearYLimit(GetLinearConstraint(), 0.f);
	Constraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.f);

	// Set rotation limits...
	Constraint->SetAngularSwing1Limit(GetAngularConstraint(), 0.f);
}

// Retrieves the appropriate linear constraint.
const ELinearConstraintMotion AMovableObject::GetLinearConstraint() const
{
	return (ELinearConstraintMotion)((const unsigned char)bOnlySimulateVertically * 2);
}

// Retrieves the appropriate angular constraint.
const EAngularConstraintMotion AMovableObject::GetAngularConstraint() const
{
	return (EAngularConstraintMotion)((const unsigned char)!bAllowPhysicsRotation * 2);
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

