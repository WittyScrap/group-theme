// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellActor.h"

// Sets default values
ASpellActor::ASpellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Geometry = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	Geometry->SetGenerateOverlapEvents(true);
	RootComponent = Geometry;
}

void ASpellActor::OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UClass* otherClass = OtherActor->GetClass();

	if (otherClass != BurnProjectile && otherClass != FreezeProjectile)
	{
		return;
	}

	bool consume = false;

	switch (State)
	{
	case TS_None:
		if (otherClass == BurnProjectile && bCanBurn)
		{
			OnBurned(OtherActor);
			OnStateChanged(OtherActor, State = TS_Burned);
			consume = true;
		}
		else if (otherClass == FreezeProjectile && bCanFreeze)
		{
			OnFrozen(OtherActor);
			OnStateChanged(OtherActor, State = TS_Frozen);
			consume = true;
		}

		break;

	case TS_Frozen:
		if (otherClass == BurnProjectile)
		{
			OnThawed(OtherActor);
			OnStateChanged(OtherActor, State = TS_None);
			consume = true;
		}
		break;

	case TS_Burned:
		if (otherClass == FreezeProjectile)
		{
			OnThawed(OtherActor);
			OnStateChanged(OtherActor, State = TS_None);
			consume = true;
		}
		break;
	}

	if (bDestroyBullet && (consume || bEvenWhenIgnored))
	{
		OtherActor->Destroy();
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

void ASpellActor::Burn(bool Force)
{
	switch (State)
	{
	case TS_None:
		if (bCanBurn || Force)
		{
			OnBurned(nullptr);
			OnStateChanged(nullptr, State = TS_Burned);
		}
		break;

	case TS_Frozen:
		OnThawed(nullptr);
		OnStateChanged(nullptr, State = TS_None);
		break;
	}
}

void ASpellActor::Freeze(bool Force)
{
	switch (State)
	{
	case TS_None:
		if (bCanFreeze || Force)
		{
			OnFrozen(nullptr);
			OnStateChanged(nullptr, State = TS_Frozen);
		}
		break;

	case TS_Burned:
		OnThawed(nullptr);
		OnStateChanged(nullptr, State = TS_None);
		break;
	}
}

const UTemperatureState& ASpellActor::GetState() const
{
	return State;
}

void ASpellActor::BeginPlay()
{
	Super::BeginPlay();

	State = InitialState;
	Geometry->OnComponentBeginOverlap.AddDynamic(this, &ASpellActor::OnOverlapDetected);
}