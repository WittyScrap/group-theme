// Fill out your copyright notice in the Description page of Project Settings.


#include "HandComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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

void UHandComponent::Fire()
{
	if (bEnabled && Cooldown < CoodownTolerance)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<AActor>(*ProjectileType, GetComponentLocation(), PointOfView->GetComponentRotation());
		}

		ResetCooldown();
		OnFired();
	}
}