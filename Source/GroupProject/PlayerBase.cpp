// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

void APlayerBase::Horizontal(float value)
{
	Movement->AddMovement(0, value);
}

void APlayerBase::Vertical(float value)
{
	Movement->AddMovement(value, 0);
}

void APlayerBase::MouseX(float value)
{
	Movement->AddRotation(value * RotationSpeedX * (!InvertX * 2 - 1));
}

void APlayerBase::MouseY(float value)
{
	float rotationDelta = value * RotationSpeedY * (!InvertY * 2 - 1);
	FRotator rotation = Camera->GetComponentRotation();
	rotation.Pitch += rotationDelta;
	rotation.Pitch = FMath::ClampAngle(rotation.Pitch, CameraPitchMin, CameraPitchMax);
	rotation.Roll = 0;
	Camera->SetWorldRotation(rotation);
}

void APlayerBase::Jump()
{
	Movement->Jump();
}

APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetSimulatePhysics(true);
	Capsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Capsule->GetBodyInstance()->bLockXRotation = true;
	Capsule->GetBodyInstance()->bLockYRotation = true;
	RootComponent = Capsule;

	Hands = CreateDefaultSubobject<USceneComponent>(TEXT("Hands"));
	Hands->SetupAttachment(RootComponent);
	Hands->SetRelativeLocation(FVector::ZeroVector);

	LeftHand = CreateDefaultSubobject<UHandComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(Hands);
	LeftHand->SetRelativeLocation(FVector::ForwardVector * 100 + FVector::LeftVector * 100);

	RightHand = CreateDefaultSubobject<UHandComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(Hands);
	RightHand->SetRelativeLocation(FVector::ForwardVector * 100 + FVector::RightVector * 100);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector::UpVector * Capsule->GetScaledCapsuleHalfHeight());

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UPlayerMovement>(TEXT("PlayerMovement"));
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerBase::Horizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerBase::Vertical);
	PlayerInputComponent->BindAxis("MouseX", this, &APlayerBase::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerBase::MouseY);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerBase::Jump);
	PlayerInputComponent->BindAction("ShootFire", IE_Pressed, this, &APlayerBase::FireSpell);
	PlayerInputComponent->BindAction("ShootIce", IE_Pressed, this, &APlayerBase::IceSpell);
}

void APlayerBase::FireSpell()
{
	LeftHand->Fire();
}

void APlayerBase::IceSpell()
{
	RightHand->Fire();
}

