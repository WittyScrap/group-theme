// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "SpellActor.generated.h"

UENUM()
enum UTemperatureState
{
	TS_None		UMETA(DisplayName = "Thawed"),
	TS_Frozen	UMETA(DisplayName = "Frozen"),
	TS_Burned	UMETA(DisplayName = "Burned")
};

UCLASS()
class GROUPPROJECT_API ASpellActor : public AActor
{
	GENERATED_BODY()

private:
	UTemperatureState State = TS_None;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)				UStaticMeshComponent* Geometry;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Actor: Filters")		UClass* BurnProjectile;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Actor: Filters")		UClass* FreezeProjectile;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Actor: Properties")	bool bCanBurn = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Actor: Properties")	bool bCanFreeze = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Actor: Properties")	bool bDestroyBullet = true;

public:
	ASpellActor();

protected:
	UFUNCTION() void OnOverlapDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	UFUNCTION(Exec) void SetFreezable(bool bState);
	UFUNCTION(Exec) void SetBurnable(bool bState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Spell Actor: Events") void OnFrozen(AActor* bullet);
	UFUNCTION(BlueprintImplementableEvent, Category = "Spell Actor: Events") void OnThawed(AActor* bullet);
	UFUNCTION(BlueprintImplementableEvent, Category = "Spell Actor: Events") void OnBurned(AActor* bullet);
	UFUNCTION(BlueprintImplementableEvent, Category = "Spell Actor: Events") void OnStateChanged(AActor* bullet, UTemperatureState state);

	UFUNCTION(BlueprintCallable, Category = "Spell Actor: State") const UTemperatureState& GetState() const;
};
