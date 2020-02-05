// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicidalController.h"

// Sets default values
ASuicidalController::ASuicidalController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->SetupAttachment(RootComponent);
	CameraSpring->SetRelativeLocationAndRotation(CameraStart, CameraTilt);
	CameraSpring->TargetArmLength = 400.0f;
	CameraSpring->bEnableCameraLag = true;
	CameraSpring->CameraLagSpeed = 6.0f;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraSpring);
}

// Called when the game starts or when spawned
void ASuicidalController::BeginPlay()
{
	Super::BeginPlay();

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

// Consumes the stored movement vector and returns it.
const FVector ASuicidalController::ConsumeMovementVector()
{
	FVector movement(StoredMovement);
	
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
}

// Called to bind functionality to input
void ASuicidalController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(XAxis, this, &ASuicidalController::OnHorizontalMovement);
	PlayerInputComponent->BindAxis(YAxis, this, &ASuicidalController::OnVerticalMovement);
	PlayerInputComponent->BindAction(AJump, IE_Pressed, this, &ASuicidalController::OnJump);
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

