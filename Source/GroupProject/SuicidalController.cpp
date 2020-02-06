// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicidalController.h"

// Sets default values
ASuicidalController::ASuicidalController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->SetupAttachment(RootComponent);
	CameraSpring->SetRelativeLocationAndRotation(CameraStart, CameraTilt);
	CameraSpring->TargetArmLength = 1000.f;
	CameraSpring->bEnableCameraLag = true;
	CameraSpring->bEnableCameraRotationLag = true;
	CameraSpring->CameraLagSpeed = 1.f;
	CameraSpring->CameraRotationLagSpeed = 1.f;
	CameraSpring->bInheritPitch = false;
	CameraSpring->bInheritRoll = false;
	CameraSpring->bInheritYaw = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraSpring);

	PlayerRoot = GetCapsuleComponent();
}

// Called when the game starts or when spawned
void ASuicidalController::BeginPlay()
{
	Super::BeginPlay();

	ToggleCursor(true);

	bool bAbs = LockOn == FocusPoint;
	CameraSpring->SetAbsolute(bAbs, bAbs, bAbs);

	if (bAbs)
	{
		CameraSpring->SetWorldLocation(FocusPointLocation);
	}

	switch (ViewMode)
	{
	case FakeOrtho:
		CameraSpring->TargetArmLength = 5000.f; // Reeeally far away...
		PlayerCamera->SetFieldOfView(20.f); // Reeeally really tight.
		// vv Fall-through vv

	case Perspective:
		PlayerCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
		break;

	case Orthogonal:
		PlayerCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
		break;
	}
}

// Is this player still alive?
const bool ASuicidalController::IsAlive() const
{
	return Alive;
}

// The rotation that should be reached.
const FRotator ASuicidalController::GetDesiredRotation() const
{
	FRotator rotator = LastRotation.ToOrientationRotator();
	rotator.Yaw -= 90.f;

	return rotator;
}

// Toggles the cursor's visibility.
void ASuicidalController::ToggleCursor(bool visible)
{
	APlayerController* controller = Cast<APlayerController>(GetController());

	if (controller)
	{
		controller->bShowMouseCursor = visible;
		controller->bEnableClickEvents = visible;
		controller->bEnableMouseOverEvents = visible;
	}
}

// Handles controller horizontal movement.
void ASuicidalController::OnHorizontalMovement(float value)
{
	RegisterHorizontalMovement(value);
}

// Handles controller vertical movement.
void ASuicidalController::OnVerticalMovement(float value)
{
	RegisterVerticalMovement(value);
}

// Horizontal camera rotation.
void ASuicidalController::OnCameraHorizontal(float value)
{
	if (State == Panning)
	{
		CameraSpring->AddRelativeRotation(FRotator(0, -value, 0));
	}
	else if (bDoResetCamera)
	{
		FRotator cameraRotation = CameraSpring->GetTargetRotation();
		FRotator targetRotation = cameraRotation;
		targetRotation.Yaw = CameraAngle;

		CameraSpring->SetRelativeRotation(targetRotation);
	}
}

// Vertical camera rotation.
void ASuicidalController::OnCameraVertical(float value)
{
	// Do... nothing?
	return;
}

// Performs a jump.
void ASuicidalController::OnJump()
{
	Jump();
}

// Shift game mode to panning
void ASuicidalController::OnShiftRotate()
{
	State = Panning;
	ToggleCursor(false);

	if (HasActorBegunPlay())
	{
		OnModeChanged(State);
	}
}

// Shift game mode to select
void ASuicidalController::OnShiftSelect()
{
	State = Selecting;
	ToggleCursor(true);

	if (HasActorBegunPlay())
	{
		OnModeChanged(State);
	}
}

// Consumes the stored movement vector and returns it.
const FVector ASuicidalController::ConsumeMovementVector()
{
	FVector movement(StoredMovement);

	if (StoredMovement.SizeSquared() > .1f)
	{
		FVector nextRotation = StoredMovement.GetSafeNormal(.1f);
		LastRotation = FMath::VInterpTo(LastRotation, nextRotation, SmoothFactor, 1.f);
	}
	
	StoredMovement.X = 0;
	StoredMovement.Y = 0;
	StoredMovement.Z = 0;

	return movement;
}

// Called every frame
void ASuicidalController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(ConsumeMovementVector(), 1.f, false);
	PlayerRoot->SetRelativeRotation(GetDesiredRotation());
}

// Called to bind functionality to input
void ASuicidalController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis

	PlayerInputComponent->BindAxis(XAxis, this, &ASuicidalController::OnHorizontalMovement);
	PlayerInputComponent->BindAxis(YAxis, this, &ASuicidalController::OnVerticalMovement);
	PlayerInputComponent->BindAxis(XMouse, this, &ASuicidalController::OnCameraHorizontal);
	PlayerInputComponent->BindAxis(YMouse, this, &ASuicidalController::OnCameraVertical);

	// Actions

	PlayerInputComponent->BindAction(AJump, IE_Pressed, this, &ASuicidalController::OnJump);
	PlayerInputComponent->BindAction(AShift, IE_Pressed, this, &ASuicidalController::OnShiftRotate);
	PlayerInputComponent->BindAction(AShift, IE_Released, this, &ASuicidalController::OnShiftSelect);
}

// Stores horizontal movement.
void ASuicidalController::RegisterHorizontalMovement(const float& value)
{
	StoredMovement.X += value;
}

// Stores vertical movement.
void ASuicidalController::RegisterVerticalMovement(const float& value)
{
	StoredMovement.Y += value;
}

