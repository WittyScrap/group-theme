// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "PlayerMovement.h"
#include "HandComponent.h"

#include "PlayerBase.generated.h"

UCLASS()
class GROUPPROJECT_API APlayerBase : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UCapsuleComponent* Capsule;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UCameraComponent* Camera;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UArrowComponent* Arrow;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UPlayerMovement* Movement;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UHandComponent* LeftHand;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) UHandComponent* RightHand;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components) USceneComponent* Hands;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") float RotationSpeedX = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") float RotationSpeedY = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool InvertX = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool InvertY = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties", meta = (Min = -90, Max = 0, ClampMin = -90, ClampMax = 0)) float CameraPitchMin = -80.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties", meta = (Min = 0, Max =  90, ClampMin = 0, ClampMax =  90)) float CameraPitchMax =  80.f;

	void Horizontal(float value);
	void Vertical(float value);
	void MouseX(float value);
	void MouseY(float value);

	void Jump();

public:
	APlayerBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Player: Actions") void FireSpell();
	UFUNCTION(BlueprintCallable, Category = "Player: Actions") void IceSpell();

};
