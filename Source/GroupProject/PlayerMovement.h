// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerMovement.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPPROJECT_API UPlayerMovement : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player: Properties") float AccelerationSpeed = 100.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player: Properties") float MaximumSpeed = 150.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player: Properties") float JumpStrength = 250.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player: Properties") bool bAirControl = false;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player: Properties") float FeetHeight = 10.f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player: Info") bool bIsGrounded;

	UCapsuleComponent* Rigidbody;

private:
	APawn* GetPawn() const;
	FVector ConsumeMovementInput();
	void HandleMovement();
	void LimitVelocity();
	void CheckGrounded(FVector hitLocation);
	UFUNCTION() void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	UPlayerMovement();

	void AddMovement(float x, float y);
	void Jump();

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Player: Actions") void ResetGrounded();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
