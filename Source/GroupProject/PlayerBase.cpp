// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

const FVector APlayerBase::Forward() const
{
	return GetCapsuleComponent()->GetForwardVector();
}

const FVector APlayerBase::Right() const
{
	return GetCapsuleComponent()->GetRightVector();
}

void APlayerBase::Horizontal(float value)
{
	AddMovementInput(Right() * value, 1.f);
}

void APlayerBase::Vertical(float value)
{
	AddMovementInput(Forward() * value, 1.f);
}

void APlayerBase::MouseX(float value)
{
	AddControllerYawInput(value * RotationSpeedX);
}

void APlayerBase::MouseY(float value)
{
	float rotationDelta = value * RotationSpeedY * (!bInvertY * 2 - 1);
	FRotator rotation = Camera->GetComponentRotation();
	rotation.Pitch += rotationDelta;
	rotation.Pitch = FMath::ClampAngle(rotation.Pitch, CameraPitchMin, CameraPitchMax);
	rotation.Roll = 0;
	Camera->SetWorldRotation(rotation);
}

APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = false;

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
	Camera->SetRelativeLocation(FVector::UpVector * GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
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

void APlayerBase::SetInvincible(const bool& state)
{
	bInvincible = state;
}

