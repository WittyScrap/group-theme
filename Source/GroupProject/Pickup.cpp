// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "PlayerBase.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = rootComponent;

	Geometry = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	Geometry->SetupAttachment(RootComponent);

	PickupArea = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Area"));
	PickupArea->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupArea->SetupAttachment(RootComponent);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	PickupArea->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapDetected);
}

void APickup::OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerBase* player = Cast<APlayerBase>(OtherActor);

	if (player)
	{
		player->OnPickedUp(this);
		Destroy();
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	t += DeltaTime / BobbingTime;

	if (t > 1.f)
	{
		t -= 1.f;
	}

	float sampledValue = BobbingCurve->GetFloatValue(t);
	Geometry->SetRelativeLocation(FVector::UpVector * sampledValue * BobbingHeight);
}

