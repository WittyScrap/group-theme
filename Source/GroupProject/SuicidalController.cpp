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
	CameraSpring->CameraRotationLagSpeed = 10.f;
	CameraSpring->bDoCollisionTest = false;
	CameraSpring->bInheritPitch = false;
	CameraSpring->bInheritRoll = false;
	CameraSpring->bInheritYaw = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraSpring);

	PlayerRoot = GetCapsuleComponent();

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
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

	LastRotation = PlayerRoot->GetComponentRotation();
}

// Is this player still alive?
const bool ASuicidalController::IsAlive() const
{
	return Alive;
}

// Pans camera to the right
void ASuicidalController::PanRight()
{
	FRotator offset(0, -90, 0);

	CameraSpring->AddRelativeRotation(offset);
	WorldDirRef.ConcatenateRotation(offset.Quaternion());
}

// Pans camera to the left
void ASuicidalController::PanLeft()
{
	FRotator offset(0, 90, 0);

	CameraSpring->AddRelativeRotation(offset);
	WorldDirRef.ConcatenateRotation(offset.Quaternion());
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

// Performs a jump.
void ASuicidalController::OnJump()
{
	Jump();
}

// The rotation this controller should face.
const FRotator& ASuicidalController::GetDesiredRotation()
{
	if (PreviousMovement.SizeSquared() >= 1.f)
	{
		FVector normalizedDirection = PreviousMovement.GetSafeNormal();
		FRotator normalizedRotation = normalizedDirection.Rotation();

		LastRotation = FMath::RInterpTo(LastRotation, normalizedRotation, SmoothFactor, 1.f);
	}

	return LastRotation;
}

// Consumes the stored movement vector and returns it.
const FVector ASuicidalController::ConsumeMovementVector()
{
	FVector movement(WorldDirRef.TransformVector(StoredMovement));

	PreviousMovement = movement;

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
	PlayerInputComponent->BindAction(ALeft, IE_Pressed, this, &ASuicidalController::PanLeft);
	PlayerInputComponent->BindAction(ARight, IE_Pressed, this, &ASuicidalController::PanRight);
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

