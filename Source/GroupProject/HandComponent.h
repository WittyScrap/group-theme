// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"

#include "HandComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPPROJECT_API UHandComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	static constexpr float CoodownTolerance = .01f;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HandComponent: Properties") TSubclassOf<AActor> ProjectileType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HandComponent: Properties") bool bEnabled = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HandComponent: Properties") float FireCooldown = 1.f;

	UCameraComponent* PointOfView;
	float Cooldown = 0;

public:
	UHandComponent();
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "HandComponent: Events") void OnFired();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ResetCooldown();

public:	
	UFUNCTION(BlueprintCallable, Category = "HandComponent: Actions") void Fire();
	UFUNCTION(BlueprintCallable, Category = "HandComponent: Actions") void SetEnabled(bool bState);
};
