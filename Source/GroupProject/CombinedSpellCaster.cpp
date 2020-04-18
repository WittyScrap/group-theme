// Fill out your copyright notice in the Description page of Project Settings.


#include "CombinedSpellCaster.h"

// Sets default values for this component's properties
UCombinedSpellCaster::UCombinedSpellCaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCombinedSpellCaster::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombinedSpellCaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombinedSpellCaster::SaveSegment(USplineMeshComponent* segment)
{
	Segments.Add(segment);
}

void UCombinedSpellCaster::ClearSegments()
{
	for (int i = 0; i < Segments.Num(); ++i)
	{
		if (Segments[i])
		{
			Segments[i]->DetachFromParent();
			Segments[i]->UnregisterComponent();
		}
	}

	Segments.Empty();
}

