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
	/**
	 * Print:
	 * Allows for a log message to be printed to either the log
	 * console or the screen.
	 *
	 */
	static FORCEINLINE void Print(FString, bool = false, FColor = FColor::Green, float = 1.f);

	// The VR headset that is used by this controller.
	IHeadMountedDisplay* VRHeadset;

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
	bool bPositionalTracking;

	////////////////////////
	// Motion controllers //
	////////////////////////

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UMotionControllerComponent* LeftHand;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UMotionControllerComponent* RightHand;

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

// ---------------------------------
// -- Inline function definitions --
// ---------------------------------

/**
 * Print:
 * Allows for a log message to be printed to either the log
 * console or the screen.
 *
 */
FORCEINLINE void AVRController::Print(FString text, bool log, FColor color, float time)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, time, color, text);
	}

	if (log)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	}
}