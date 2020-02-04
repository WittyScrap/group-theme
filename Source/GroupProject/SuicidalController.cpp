// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicidalController.h"

// Sets default values
ASuicidalController::ASuicidalController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = GetRootComponent();

	PlayerGraphics = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Graphics"));
	CameraSmoothener = CreateDefaultSubobject<USpringArmComponent>(TEXT("Smoothener"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	PlayerGraphics->SetupAttachment(root);
	CameraSmoothener->SetupAttachment(root);
	Camera->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ASuicidalController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuicidalController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASuicidalController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

