// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

///////////////////////////////////////////
#include "SuicidalController.generated.h"//
///////////////////////////////////////////

UCLASS()
//
// Class name: ASuicidalController
// Tasks:
//
//	* Handles input, generating events where needed
//  * Handles death events, spawn events, level reset events
//	* TBD
class GROUPPROJECT_API ASuicidalController : public ACharacter
{
	GENERATED_BODY()

	//
	// Constant data
	//

	// Translation axis
	const FName XAxis = "MoveForward";
	const FName YAxis = "MoveLeft";

	// Actions
	const FName AJump = "Jump";
	
protected:
	// Manages player graphics side.
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* PlayerGraphics;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	FVector StoredMovement;

public:
	// Sets default values for this character's properties
	ASuicidalController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Horizontal movement event
	virtual void OnHorizontalMovement(float value);

	// Vertical movement event
	virtual void OnVerticalMovement(float value);

	// Jump event
	virtual void OnJump();

	// Consumes the stored movement vector and returns it.
	const FVector ConsumeMovementVector();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Registers a new horizontal movement.
	UFUNCTION(BlueprintCallable, Category = "Robot Movement")
	void RegisterHorizontalMovement(const float& value);

	// Registers a new vertical movement.
	UFUNCTION(BlueprintCallable, Category = "Robot Movement")
	void RegisterVerticalMovement(const float& value);
};
