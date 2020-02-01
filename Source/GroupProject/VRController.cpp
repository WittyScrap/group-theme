// Fill out your copyright notice in the Description page of Project Settings.


#include "VRController.h"
#include "IXRTrackingSystem.h"

// Sets default values
AVRController::AVRController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* ------ Create VR components ------- */

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Root"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("VR Camera"));
	Camera->SetupAttachment(VRRoot);

	/* ------- Create VR controllers --------- */

	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("VR Left Hand"));
	LeftHand->SetupAttachment(VRRoot);
	LeftHand->SetTrackingSource(EControllerHand::Left);

	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("VR Right Hand"));
	RightHand->SetupAttachment(VRRoot);
	RightHand->SetTrackingSource(EControllerHand::Right);

	if (LeftHand)
	{
		LeftHand->SetIsReplicated(true);
	}

	if (RightHand)
	{
		RightHand->SetIsReplicated(true);
	}
}

// Called when the game starts or when spawned
void AVRController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVRController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Gets the current HMD connected to this device and used by this controller.
IHeadMountedDisplay* AVRController::GetCurrentHMD()
{
	if (!VRHeadset)
	{
		if (!GEngine)
		{
			return NULL;
		}

		VRHeadset = GEngine->XRSystem->GetHMDDevice();
	}

	return VRHeadset;
}

// Gets the current position of various VR components.
void AVRController::GetVRPositions(FTransform& head, FTransform& leftHand, FTransform& rightHand) const
{
	if (!GEngine)
	{
		head = FTransform::Identity;
		leftHand = FTransform::Identity;
		rightHand = FTransform::Identity;

		return;
	}

	const auto& xrSystem = GEngine->XRSystem;

	FTransform trackingToWorld = xrSystem->GetTrackingToWorldTransform();
	FTransform headTracking;

	FVector headTrackingLocation;
	FQuat headTrackingRotation;

	xrSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, headTrackingRotation, headTrackingLocation);

	headTracking.SetLocation(headTrackingLocation);
	headTracking.SetRotation(headTrackingRotation);

	head = headTracking * trackingToWorld;
	leftHand = FTransform(LeftHand->GetComponentRotation(), LeftHand->GetComponentLocation());
	rightHand = FTransform(RightHand->GetComponentRotation(), RightHand->GetComponentLocation());
}

