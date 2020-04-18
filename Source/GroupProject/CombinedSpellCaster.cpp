// Fill out your copyright notice in the Description page of Project Settings.


#include "CombinedSpellCaster.h"

// Sets default values for this component's properties
UCombinedSpellCaster::UCombinedSpellCaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Turn off prediction by default so as to not
// have a dangling line pointing to nowhere...
void UCombinedSpellCaster::BeginPlay()
{
	Super::BeginPlay();
	DisablePrediction();
}


// Called every frame
void UCombinedSpellCaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bPredicting && Camera)
	{
		FVector&& projectileVelocity = Camera->GetForwardVector() * ProjectileSpeed;


	}
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

void UCombinedSpellCaster::EnablePrediction()
{
	bPredicting = true;

	// Make line visible...
	for (USplineMeshComponent*& segment : Segments)
	{
		segment->bVisible = true;
	}
}

void UCombinedSpellCaster::DisablePrediction()
{
	bPredicting = false;

	// Make line invisible...
	for (USplineMeshComponent*& segment : Segments)
	{
		segment->bVisible = false;
	}
}

void UCombinedSpellCaster::Fire()
{
	
}

