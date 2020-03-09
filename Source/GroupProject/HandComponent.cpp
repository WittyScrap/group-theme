// Fill out your copyright notice in the Description page of Project Settings.


#include "HandComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UHandComponent::UHandComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHandComponent::BeginPlay()
{
	Super::BeginPlay();

	PointOfView = GetOwner()->FindComponentByClass<UCameraComponent>();
	Cooldown = 0;
}

void UHandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Cooldown > 0)
	{
		Cooldown -= DeltaTime;

		if (Cooldown < 0)
		{
			Cooldown = 0;
		}
	}
}

void UHandComponent::ResetCooldown()
{
	Cooldown = FireCooldown;
}

void UHandComponent::FireTowardRotation(const FRotator& Target)
{
	if (bEnabled && Cooldown < CoodownTolerance)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<AActor>(*ProjectileType, GetComponentLocation(), Target);
		}

		ResetCooldown();
		OnFired();
	}
}

void UHandComponent::FireForward()
{
	FireTowardRotation(PointOfView->GetComponentRotation());
}

void UHandComponent::Fire(const FVector& Target)
{
	const FVector& from = GetComponentLocation();

	FVector		direction (Target - from);
	FVector		up		  (PointOfView->GetUpVector());
	FVector		right	  (FVector::CrossProduct(up, direction));
	FRotator	rotation  (UKismetMathLibrary::MakeRotationFromAxes(direction, right, up));

	FireTowardRotation(rotation);
}

void UHandComponent::SetEnabled(bool bState)
{
	bEnabled = bState;
}
