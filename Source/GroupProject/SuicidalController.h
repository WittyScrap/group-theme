// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

///////////////////////////////////////////
#include "SuicidalController.generated.h"//
///////////////////////////////////////////

UCLASS()
//
// Class name: ASuicidalController
// Tasks:
//
//	* Handles input, generating events where needed
//  * Handles death events, spawn events, level reset events
//	* TBD
class GROUPPROJECT_API ASuicidalController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASuicidalController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
