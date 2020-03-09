// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "PlayerMovement.h"
#include "HandComponent.h"
#include "Pickup.h"

#include "PlayerBase.generated.h"

UCLASS()
class GROUPPROJECT_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UCameraComponent*	Camera;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UHandComponent*	LeftHand;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UHandComponent*	RightHand;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) USceneComponent*	Hands;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") float	RotationSpeedX = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") float	RotationSpeedY = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool	bInvertX = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool	bInvertY = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool	bInvincible = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool	bAlive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties", meta = (Min = -90, Max = 0, ClampMin = -90, ClampMax = 0)) float CameraPitchMin = -80.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties", meta = (Min = 0, Max =  90, ClampMin = 0, ClampMax =  90)) float CameraPitchMax =  80.f;

	const FVector Forward() const;
	const FVector Right() const;
	const FVector LookPoint() const;

	void Horizontal(float value);
	void Vertical(float value);
	void MouseX(float value);
	void MouseY(float value);

	void SwimVertical(float value);

public:
	APlayerBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Player: Actions") void FireSpell();
	UFUNCTION(BlueprintCallable, Category = "Player: Actions") void IceSpell();

	UFUNCTION(BlueprintImplementableEvent, Category = "Player: Events") void OnPickedUp(APickup* PickedUp);

	UFUNCTION(Exec) void SetInvincible(const bool& state);
	UFUNCTION(Exec) void UnlockHand();
};
