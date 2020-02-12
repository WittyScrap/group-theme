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
	Capsule->AddRelativeRotation(FRotator(0, value * RotationSpeedX * (!InvertX * 2 - 1), 0));
}

void APlayerBase::MouseY(float value)
{
	Camera->AddRelativeRotation(FRotator(value * RotationSpeedY * (!InvertY * 2 - 1), 0, 0));
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
}

