// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Pickup.generated.h"

UCLASS()
class GROUPPROJECT_API APickup : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)			UStaticMeshComponent* Geometry;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)			USphereComponent* PickupArea;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Pickup: Properties") UCurveFloat* BobbingCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup: Properties")	float BobbingTime = 6.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup: Properties")	float BobbingHeight = 50.f;

	float t = 0;

public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	virtual void BeginPlay() override;
	UFUNCTION() void OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
