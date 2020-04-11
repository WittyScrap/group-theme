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

		// Camera Sway
		FVector position = BodyRoot->RelativeLocation;
		position.Y = FMath::Lerp(position.Y, -value * SwayStrength, SwaySmoothness);
		BodyRoot->SetRelativeLocation(position);
	}
}

void APlayerBase::Vertical(float value)
{
	if (bAlive)
	{
		AddMovementInput(Forward() * value, 1.f);

		// Camera Sway
		FVector position = BodyRoot->RelativeLocation;
		position.X = FMath::Lerp(position.X, -value * SwayStrength, SwaySmoothness);
		BodyRoot->SetRelativeLocation(position);
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

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector::UpVector * GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	BodyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BodyRoot"));
	BodyRoot->SetupAttachment(Camera);
	BodyRoot->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	Hands = CreateDefaultSubobject<USceneComponent>(TEXT("Hands"));
	Hands->SetupAttachment(BodyRoot);
	Hands->SetRelativeLocation(FVector(30.f, 0.f, -8.f));

	LeftHand = CreateDefaultSubobject<UHandComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(Hands);
	LeftHand->SetRelativeLocation(FVector(2.f, -15.f, -1.5f));

	RightHand = CreateDefaultSubobject<UHandComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(Hands);
	RightHand->SetRelativeLocation(FVector(2.f, 15.f, -1.5f));
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
		//LeftHand->Fire(LookPoint());
		LeftHand->FireForward();
	}
}

void APlayerBase::IceSpell()
{
	if (bAlive)
	{
		//RightHand->Fire(LookPoint());
		RightHand->FireForward();
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

