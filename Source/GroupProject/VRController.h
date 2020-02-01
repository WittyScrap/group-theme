// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeadMountedDisplay.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"

///////////////////////////////////////////
#include "VRController.generated.h" /////// Leave last!
///////////////////////////////////////////

UCLASS()
class GROUPPROJECT_API AVRController : public ACharacter
{
	GENERATED_BODY()

private:
	// The VR headset that is used by this controller.
	IHeadMountedDisplay* VRHeadset;

	// Configures a motion controller as a VR hand of the given type.
	void SetupHand(UMotionControllerComponent* target, const EControllerHand& hand);

public:
	// Sets default values for this character's properties
	AVRController();

protected:
	// Root component for VR controller subobjects.
	UPROPERTY(EditDefaultsOnly, Category = "VR Components")
	USceneComponent* VRRoot;

	// Target camera
	UPROPERTY(VisibleAnywhere, Category = "VR Components")
	UCameraComponent* Camera;

	// Used to specify the origin of the HMD
	UPROPERTY(VisibleAnywhere, Category = "VR Components")
	USceneComponent* VROrigin;

	// Used to specify whether or not positional tracking will be used
	UPROPERTY(EditDefaultsOnly, Category = "VR Settings")
	bool bPositionalTracking = true;

	////////////////////////
	// Motion controllers //
	////////////////////////

	// The left VR controller.
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UMotionControllerComponent* LeftHand;

	// The right VR controller.
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UMotionControllerComponent* RightHand;

	UPROPERTY(EditDefaultsOnly, Category = "VR Settings")
	bool bDisplayHands = true;

	UPROPERTY(EditDefaultsOnly, Category = "VR Settings", meta = (EditCondition = "bDisplayHands"))
	bool bUseCustomHands = true;

	// The mesh object for rendering both hands (will be mirrored on the X-axis automatically).
	UPROPERTY(EditDefaultsOnly, Category = "Graphics Components", meta = (EditCondition = "bUseCustomHands"))
	UStaticMesh* HandMesh;

	/////////////
	// Methods //
	/////////////

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// The HMD that is currently being used by this class
	IHeadMountedDisplay* GetCurrentHMD();

	// The positions of the main VR components.
	UFUNCTION(BlueprintCallable, Category = "VR tools")
	void GetVRPositions(FTransform& head, FTransform& lHand, FTransform& rHand) const;
};