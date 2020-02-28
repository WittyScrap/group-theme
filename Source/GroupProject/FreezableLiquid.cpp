// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezableLiquid.h"

// Sets default values
AFreezableLiquid::AFreezableLiquid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Geometry = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	Geometry->SetRelativeLocation(FVector::ZeroVector);
	RootComponent = Geometry;
}

void AFreezableLiquid::BeginPlay()
{
	Geometry->OnComponentBeginOverlap.AddDynamic(this, &AFreezableLiquid::OnOverlapDetected);
}

void AFreezableLiquid::OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector2D hit(OtherActor->GetActorLocation());

	if (CanSpawnIslands(OtherActor))
	{
		CreateIsland(hit);
		OnPlatformCreated(hit);

		// Destroy projectile to prevent it from bouncing and creating another island.
		OtherActor->Destroy();
	}
	else
	{
		OnEntityEntered(OtherActor, hit);
	}
}

void AFreezableLiquid::CreateIsland(const FVector2D& location)
{
	FVector worldLocation = FVector(location.X, location.Y, GetActorLocation().Z);
	UWorld* world = GetWorld();

	if (world)
	{
		world->SpawnActor<AActor>(*IslandPrefab, worldLocation, FRotator::ZeroRotator);
	}
}

bool AFreezableLiquid::CanSpawnIslands(const AActor* hit) const
{
	return hit->GetClass() == ProjectileFilter;
}

