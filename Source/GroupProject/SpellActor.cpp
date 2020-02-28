// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellActor.h"

// Sets default values
ASpellActor::ASpellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Geometry = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	Geometry->SetGenerateOverlapEvents(true);
	Geometry->OnComponentBeginOverlap.AddDynamic(this, &ASpellActor::OnOverlapDetected);
	RootComponent = Geometry;
}

void ASpellActor::OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == BurnProjectile && bCanBurn)
	{
		switch (State)
		{
		case TS_None:
			OnBurned(OtherActor);
			break;

		case TS_Frozen:
			OnThawed(OtherActor);
			break;
		}

		return;
	}

	if (OtherActor->GetClass() == FreezeProjectile && bCanFreeze)
	{
		switch (State)
		{
		case TS_None:
			OnFrozen(OtherActor);
			break;

		case TS_Burned:
			OnThawed(OtherActor);
			break;
		}

		return;
	}
}

void ASpellActor::SetFreezable(bool bState)
{
	bCanFreeze = bState;
}

void ASpellActor::SetBurnable(bool bState)
{
	bCanBurn = bState;
}

const UTemperatureState& ASpellActor::GetState() const
{
	return State;
}
