// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicidalController.h"
#include "MovableObject.h"

// Sets default values
ASuicidalController::ASuicidalController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(CharacterRadius, CharacterHeight * .5f);
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	CapsuleComponent->SetNotifyRigidBodyCollision(true);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	CapsuleComponent->BodyInstance.bLockXRotation = true;
	CapsuleComponent->BodyInstance.bLockYRotation = true;
	CapsuleComponent->BodyInstance.bLockZRotation = false;
	RootComponent = CapsuleComponent;

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

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraSpring);
}

// AirControl or IsGrounded?
const bool ASuicidalController::CanControl() const
{
	return bAirControl || IsGrounded();
}

// Called when the game starts or when spawned
void ASuicidalController::BeginPlay()
{
	Super::BeginPlay();

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

	CapsuleComponent->OnComponentHit.AddDynamic(this, &ASuicidalController::PerformGroundedCheck);
	LastRotation = CapsuleComponent->GetComponentRotation();
}

// Converts directions from local to world space using transform.
const FVector ASuicidalController::ToWorld(const FVector& relativeDirection)
{
	return WorldDirRef.TransformVector(relativeDirection);
}

// Is this player still alive?
const bool ASuicidalController::IsAlive() const
{
	return bAlive;
}

// Is this player grounded?
const bool ASuicidalController::IsGrounded() const
{
	return Ground != nullptr;
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
void ASuicidalController::Jump()
{
	if (Ground)
	{
		CapsuleComponent->AddImpulse(FVector::UpVector * JumpStrength);
		Ground = nullptr;
	}
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
	PreviousMovement = ConsumeMovementInputVector();
	return PreviousMovement;
}

// Stops the controller from moving too quickly.
void ASuicidalController::LimitControllerVelocity()
{
	CapsuleComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	FVector velocity(CapsuleComponent->GetPhysicsLinearVelocity());

	if (velocity.SizeSquared() > (MovementSpeed * MovementSpeed))
	{
		FVector newVelocity = velocity.GetClampedToMaxSize(MovementSpeed);
		newVelocity.Z = velocity.Z;

		CapsuleComponent->SetPhysicsLinearVelocity(newVelocity);
	}

	ApplyDrag(velocity);
}

// Decelerates this controller.
void ASuicidalController::ApplyDrag(FVector& velocity)
{
	if (velocity.SizeSquared() > (DecelerationSpeed * DecelerationSpeed))
	{
		velocity.Normalize();

		UGameUtils::NegateVector(velocity);
		UGameUtils::MultiplyVector(velocity, DecelerationSpeed);

		velocity.Z = 0;

		CapsuleComponent->AddImpulse(velocity);
	}
	else
	{
		CapsuleComponent->SetPhysicsLinearVelocity(FVector::UpVector * velocity.Z);
	}
}

// Removes small amounts of velocity.
void ASuicidalController::ClearDanglingVelocity()
{
	FVector velocity(CapsuleComponent->GetPhysicsLinearVelocity());

	if (velocity.SizeSquared() < SpeedTolerance)
	{
		CapsuleComponent->SetPhysicsLinearVelocity(FVector::UpVector * velocity.Z);
	}
}

// Performs grounded check.
void ASuicidalController::PerformGroundedCheck(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitComp == CapsuleComponent && OtherComp != Ground)
	{
		FVector hitPoint = Hit.ImpactPoint;
		hitPoint = GetTransform().InverseTransformPosition(hitPoint);

		if (hitPoint.Z < FeetHeight)
		{
			Ground = OtherComp;
		}
	}
}

// Called every frame
void ASuicidalController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanControl())
	{
		ClearDanglingVelocity();
		CapsuleComponent->AddImpulse(ConsumeMovementVector());
		CapsuleComponent->SetRelativeRotation(GetDesiredRotation());
		LimitControllerVelocity();
	}
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

	PlayerInputComponent->BindAction(AJump, IE_Pressed, this, &ASuicidalController::Jump);
	PlayerInputComponent->BindAction(ALeft, IE_Pressed, this, &ASuicidalController::PanLeft);
	PlayerInputComponent->BindAction(ARight, IE_Pressed, this, &ASuicidalController::PanRight);
}

// Stores horizontal movement.
void ASuicidalController::RegisterHorizontalMovement(const float& value)
{
	if (CanControl())
	{
		AddMovementInput(ToWorld(FVector::ForwardVector), value * AccelerationSpeed);
	}
}

// Stores vertical movement.
void ASuicidalController::RegisterVerticalMovement(const float& value)
{
	if (CanControl())
	{
		AddMovementInput(ToWorld(FVector::RightVector), value * AccelerationSpeed);
	}
}

