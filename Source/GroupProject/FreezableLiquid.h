// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "FreezableLiquid.generated.h"

UCLASS()
class GROUPPROJECT_API AFreezableLiquid : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components) UStaticMeshComponent* Geometry;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Freezable Liquid: Properties") TSubclassOf<AActor> IslandPrefab;

	virtual void BeginPlay() override;
	UFUNCTION() void OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent, Category = "Freezable Liquid: Events") void OnWaterEntered(FVector2D location);

public:	
	// Sets default values for this actor's properties
	AFreezableLiquid();
	UFUNCTION(BlueprintCallable, Category = "Freezable Liquid: Actions") void CreateIsland(const FVector2D& location);
};
