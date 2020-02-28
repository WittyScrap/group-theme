// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovement.h"

APawn* UPlayerMovement::GetPawn() const
{
	return Cast<APawn>(GetOwner());
}

FVector UPlayerMovement::ConsumeMovementInput()
{
	return GetPawn()->ConsumeMovementInputVector();
}

void UPlayerMovement::HandleMovement()
{
	FVector impulse = ConsumeMovementInput();
	Rigidbody->AddImpulse(impulse, NAME_None, true);
}

void UPlayerMovement::LimitVelocity()
{
	FVector velocity = Rigidbody->GetPhysicsLinearVelocity();

	if (velocity.SizeSquared() > MaximumSpeed)
	{
		FVector v = velocity.GetClampedToMaxSize(MaximumSpeed);
		v.Z = velocity.Z;
		Rigidbody->SetPhysicsLinearVelocity(v);
	}

	Rigidbody->SetPhysicsAngularVelocity(FVector::ZeroVector);

	FRotator anomalousRotation = Rigidbody->GetComponentRotation();
	anomalousRotation.Roll = 0.f;
	anomalousRotation.Pitch = 0.f;

	Rigidbody->SetWorldRotation(anomalousRotation);
}

void UPlayerMovement::CheckGrounded(FVector hitLocation)
{
	float feet = FindFeet();

	if (!bIsGrounded && hitLocation.Z < feet)
	{
		bIsGrounded = true;
		CancelBounce();
	}
}

void UPlayerMovement::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitComp == Rigidbody)
	{
		CheckGrounded(Hit.ImpactPoint);
	}
}

void UPlayerMovement::CancelBounce()
{
	FVector vel = Rigidbody->GetPhysicsLinearVelocity();
	vel.Z = 0;

	Rigidbody->SetPhysicsLinearVelocity(vel);
}

// Sets default values for this component's properties
UPlayerMovement::UPlayerMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovement::AddMovement(float x, float y)
{
	GetPawn()->AddMovementInput(Rigidbody->GetForwardVector() * x + Rigidbody->GetRightVector() * y, AccelerationSpeed);
	ExpectedVelocity = Rigidbody->GetPhysicsLinearVelocity();
}

void UPlayerMovement::AddRotation(float h)
{
	CapsuleRotation.Yaw += h;
}

void UPlayerMovement::Jump()
{
	if (bIsGrounded)
	{
		Rigidbody->AddImpulse(FVector::UpVector * JumpStrength, NAME_None, true);
		ResetGrounded();
	}
}

// Called when the game starts
void UPlayerMovement::BeginPlay()
{
	Super::BeginPlay();
	Rigidbody = Cast<UCapsuleComponent>(GetPawn()->GetComponentByClass(UCapsuleComponent::StaticClass()));
	Rigidbody->OnComponentHit.AddDynamic(this, &UPlayerMovement::OnHit);
	SetTickGroup(ETickingGroup::TG_PostPhysics);

	CapsuleRotation = Rigidbody->GetComponentRotation();
}

void UPlayerMovement::ResetGrounded()
{
	bIsGrounded = false;
}

float UPlayerMovement::FindFeet() const
{
	float worldZ = Rigidbody->GetComponentLocation().Z;
	float halfH = Rigidbody->GetScaledCapsuleHalfHeight();

	return worldZ - (halfH - FeetHeight);
}

const FVector& UPlayerMovement::GetExpectedVelocity() const
{
	return ExpectedVelocity;
}

// Called every frame
void UPlayerMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleMovement();
	LimitVelocity();

	Rigidbody->SetWorldRotation(CapsuleRotation);
}

