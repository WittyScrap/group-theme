// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "DrawDebugHelpers.h"

const FVector APlayerBase::Forward() const
{
	return GetCapsuleComponent()->GetForwardVector();
}

const FVector APlayerBase::Right() const
{
	return GetCapsuleComponent()->GetRightVector();
}

const FVector APlayerBase::LookPoint() const
{
	const FVector lineTraceStart(Camera->GetComponentLocation());
	const FVector lineTraceEnd(Camera->GetComponentLocation() + Camera->GetForwardVector() * 0xFFFFFF); // Far, far away...

	FCollisionQueryParams params;
	FHitResult outHit;

	if (GetWorld()->LineTraceSingleByChannel(outHit, lineTraceStart, lineTraceEnd, ECC_Visibility, params))
	{
		return outHit.ImpactPoint;
	}
	else
	{
		return lineTraceEnd;
	}
}

void APlayerBase::Horizontal(float value)
{
	if (bAlive)
	{
		AddMovementInput(Right() * value, 1.f);
	}
}

void APlayerBase::Vertical(float value)
{
	if (bAlive)
	{
		AddMovementInput(Forward() * value, 1.f);
	}
}

void APlayerBase::MouseX(float value)
{
	if (bAlive)
	{
		AddControllerYawInput(value * RotationSpeedX);
	}
}

void APlayerBase::MouseY(float value)
{
	if (bAlive)
	{
		float rotationDelta = value * RotationSpeedY * (!bInvertY * 2 - 1);
		FRotator rotation = Camera->GetComponentRotation();
		rotation.Pitch += rotationDelta;
		rotation.Pitch = FMath::ClampAngle(rotation.Pitch, CameraPitchMin, CameraPitchMax);
		rotation.Roll = 0;
		Camera->SetWorldRotation(rotation);
	}
}

void APlayerBase::SwimVertical(float value)
{
	if (bAlive)
	{
		AddMovementInput(FVector::UpVector, 1.f);
	}
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
	PlayerInputComponent->BindAxis("Swim", this, &APlayerBase::SwimVertical);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerBase::Jump);
	PlayerInputComponent->BindAction("ShootFire", IE_Pressed, this, &APlayerBase::FireSpell);
	PlayerInputComponent->BindAction("ShootIce", IE_Pressed, this, &APlayerBase::IceSpell);
}

void APlayerBase::FireSpell()
{
	if (bAlive)
	{
		LeftHand->Fire(LookPoint());
	}
}

void APlayerBase::IceSpell()
{
	if (bAlive)
	{
		RightHand->Fire(LookPoint());
	}
}

void APlayerBase::SetInvincible(const bool& state)
{
	bInvincible = state;
}

void APlayerBase::UnlockHand()
{
	RightHand->SetEnabled(true);
}

