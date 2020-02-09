// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"

///////////////////////////////////////////
#include "SuicidalController.generated.h"//
///////////////////////////////////////////

/*
 * Forward declaration for:
 * AMovableObject class.
 *
 */
class AMovableObject;

UENUM()
enum LockMode
{
	Player		UMETA(DisplayName = "Lock on Player"),
	FocusPoint	UMETA(DisplayName = "Lock on Focus Point")
};

UENUM()
enum CameraMode
{
	Perspective UMETA(DisplayName = "Full Perspective"),
	Orthogonal	UMETA(DisplayName = "Real Orthogonal"),
	FakeOrtho	UMETA(DisplayName = "False Orthogonal")
};

UCLASS()
//
// Class name: ASuicidalController
// Tasks:
//
//	* Handles input, generating events where needed
//  * Handles death events, spawn events, level reset events
//	* TBD
class GROUPPROJECT_API ASuicidalController : public APawn
{
	GENERATED_BODY()

	//
	// Constant data
	//
	
	// Input
	const FName XAxis = "MoveForward";
	const FName YAxis = "MoveLeft";
	const FName XMouse = "CameraHorizontal";
	const FName YMouse = "CameraVertical";
	const FName AJump = "Jump";
	const FName ALeft = "PanLeft";
	const FName ARight = "PanRight";
	
protected:

	// The object being held by this controller
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Components)
	AMovableObject* HeldObject;

	// The main capsule that handles all physics based interactions.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UCapsuleComponent* CapsuleComponent;

	// The reference forward arrow component.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UArrowComponent* ArrowComponent;

	// The active mesh being used to render the player.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	USkeletalMeshComponent* Mesh;

	// The camera spring component that handles controlling the camera's position, distance and orientation.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USpringArmComponent* CameraSpring;

	// The rendering player camera that will automatically be possessed.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	UCameraComponent* PlayerCamera;

	// The previous frame's stored movement.
	UPROPERTY()
	FVector PreviousMovement;

	// Whether or not this controller is alive.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SuicidalController: Stats")
	bool Alive = true;

	// The amount to smoothen the controller's rotation.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "SuicidalController: Movement Settings", meta = (Min = 0, Max = 1, ClampMin = 0, ClampMax = 1))
	float SmoothFactor = .5f;

	// Where the camera should lock on.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "SuicidalController: Preferences")
	TEnumAsByte<LockMode> LockOn = FocusPoint;

	// The location the camera should focus on, if LockOn is set to FocusPoint. This will be ignored if LockOn is set to Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuicidalController: Preferences", meta = (EditCondition = "LockOn == FocusPoint"))
	FVector FocusPointLocation;

	// The view mode for the camera.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuicidalController: Preferences")
	TEnumAsByte<CameraMode> ViewMode = FakeOrtho;

	// The angle the camera should pitch down.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SuicidalController: Preferences")
	float CameraAngle = 45.f;

	// The height of the physics capsule for the character.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SuicidalController: Preferences")
	float CharacterHeight = 100.f;

	// The radius of the physics capsule for the character.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SuicidalController: Preferences")
	float CharacterRadius = 25.f;
	
	// The horizontal movement speed.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuicidalController: Movement Settings")
	float AccelerationSpeed = 100.f;

	// The horizontal movement speed.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuicidalController: Movement Settings")
	float MovementSpeed = 100.f;

	// The jump strength.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuicidalController: Movement Settings")
	float JumpStrength = 500.f;

	//
	// Top-down camera properties...
	//

	FVector		CameraStart = FVector(-100.f, 0.f, 200.f);
	FRotator	CameraTilt = FRotator(-45.f, 0.f, 0.f);
	FTransform	WorldDirRef = FTransform(FRotator::ZeroRotator, FVector::ZeroVector);
	FRotator	LastRotation = FRotator(0, 0, 0);

public:

	/*
	 * Creates a new suicidal controller character
	 * using default component values and generated
	 * types.
	 *
	 */
	ASuicidalController();

	/* 
	 * Checks whether or not this character is alive.
	 *
	 * @return Whether or not this character is alive.
	 */
	UFUNCTION(BlueprintPure, Category = "Stats")
	const bool IsAlive() const;

protected:

	/*
	 * Event method invoked when the game has
	 * just begun.
	 *
	 */
	virtual void BeginPlay() override;

	/*
	 * Converts a relative-direction vector to a world vector
	 * relative to the internal transform.
	 *
	 */
	const FVector ToWorld(const FVector& relativeDirection);

	/*
	 * Overridable method that gets invoked when the character
	 * dies.
	 *
	 * @param reason The death reason (e.g. Fell from a high place).
	 * @return The direction this actor should face.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = SuicidalController)
	void OnDied(const FString& reason);

	/*
	 * Pans the camera to the right by 90 degrees.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = SuicidalController)
	void PanRight();

	/*
	 * Pans the camera to the right by -90 degrees.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = SuicidalController)
	void PanLeft();

	/*
	 * Handles character movement on the horizontal (left/right) axis
	 * relative to where the camera is facing.
	 *
	 * @param value The amount of movement.
	 */
	void OnHorizontalMovement(float value);

	/*
	 * Handles character movement on the vertical (forward/backward) axis
	 * relative to where the camera is facing.
	 *
	 * @param value The amount of movement.
	 */
	void OnVerticalMovement(float value);

	/*
	 * Handles cameva rotation movement on the horizontal axis.
	 *
	 * @param value The amount of rotation.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = SuicidalController)
	void OnCameraHorizontal(float value);

	/*
	 * Handles cameva rotation movement on the vertical axis.
	 *
	 * @param value The amount of rotation.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = SuicidalController)
	void OnCameraVertical(float value);

	/*
	 * Handles the character jumping.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = SuicidalController)
	void Jump();

	/*
	 * Retrieves the rotation that this controller should be facing
	 * given the last movement vector.
	 *
	 * @return The rotation this controller should face.
	 */
	UFUNCTION(BlueprintCallable, Category = "Tools")
	const FRotator& GetDesiredRotation();

private:

	/*
	 * Consumes the movement vector and returns its previous value.
	 * This will reset the movement vector to its default value of
	 * (0, 0, 0), and set the look direction to the previous value
	 * of the movement vector.
	 *
	 * @return The direction this actor should face.
	 */
	const FVector ConsumeMovementVector();

public:

	/*
	 * Event handler called on every frame (tick).
	 *
	 * @param value The time difference between this frame and the previous frame (ie. how long the previous frame took to render).
	 */
	virtual void Tick(float DeltaTime) override;

	/*
	 * Prepares user input and binds all necessary axis to mehods.
	 *
	 * @param value The player input component.
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	 * Saves horizontal movement and uses it on the next tick.
	 *
	 * @param value The amount of movement to register.
	 */
	UFUNCTION(BlueprintCallable, Category = "Robot Movement")
	void RegisterHorizontalMovement(const float& value);

	/*
	 * Saves vertical movement and uses it on the next tick.
	 *
	 * @param value The amount of movement to register.
	 */
	UFUNCTION(BlueprintCallable, Category = "Robot Movement")
	void RegisterVerticalMovement(const float& value);
};
