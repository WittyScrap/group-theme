// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HandComponent.h"
#include "Components/SplineComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SplineMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "CombinedSpellCaster.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPPROJECT_API UCombinedSpellCaster : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY() TArray<USplineMeshComponent*> Segments;
	UPROPERTY() bool bPredicting;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spell Caster: Spawn Properties") TSubclassOf<AActor> ProjectileType;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spell Caster: Spawn Properties") UStaticMesh* LineMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spell Caster: Spawn Properties") TEnumAsByte<ESplineMeshAxis::Type> SplineForward;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Spell Caster: Spawn Properties") UHandComponent* LeftHand;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Spell Caster: Spawn Properties") UHandComponent* RightHand;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Spell Caster: Spawn Properties") UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Caster: Trajectory") float ProjectileSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Caster: Trajectory") float ProjectileGravity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Caster: Trajectory", meta = (ClampMin = 2)) int Resolution = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spell Caster: Trajectory", meta = (Min = 0, Max = 100, ClampMin = 0, ClampMax = 100)) float LineWidth = 10;

	USplineComponent* ReferenceTrail;

	// Sets default values for this component's properties
	UCombinedSpellCaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SaveSegment(USplineMeshComponent* segment);
	void ClearSegments();
		
	UFUNCTION(BlueprintPure, Category = "Spell Caster: Stats") bool		Predicting()	{ return bPredicting; }
	UFUNCTION(BlueprintPure, Category = "Spell Caster: Stats") float	Gravity()		{ return ProjectileGravity > 0 ? -ProjectileGravity : ProjectileGravity; }

	UFUNCTION(BlueprintCallable, Category = "Spell Caster: Actions") void EnablePrediction();
	UFUNCTION(BlueprintCallable, Category = "Spell Caster: Actions") void DisablePrediction();
	UFUNCTION(BlueprintCallable, Category = "Spell Caster: Actions") void Fire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Spell Caster: Events") void OnProjectileFired(const AActor* projectile);
};
