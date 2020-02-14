// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "PlayerMovement.h"

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") float RotationSpeedX = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") float RotationSpeedY = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool InvertX = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerBase: Properties") bool InvertY = false;

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

};
