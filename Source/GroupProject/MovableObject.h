// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SuicidalController.h"

/////////////////////////////////////////
#include "MovableObject.generated.h"/////
/////////////////////////////////////////

/*
 * Represents any object that can be moved around and
 * picked up.
 *
 */
UCLASS()
class GROUPPROJECT_API AMovableObject : public AStaticMeshActor
{
	GENERATED_BODY()

protected:

	// The actor holding this mesh (if any).
	UPROPERTY()
	ASuicidalController* Holder = nullptr;
	
public:	
	/*
	 * Sets default values for this actor's properties
	 *
	 */
	AMovableObject();

	/*
	 * Called every frame
	 *
	 */
	virtual void Tick(float DeltaTime) override;

	/*
	 * Whether or not this object is being held by a
	 * controller.
	 *
	 * @return True if this object is being held, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "States")
	const bool IsHeld() const;

	/*
	 * The actor holding this object, if any exists.
	 *
	 * @return The actor that holds this object, this will be null if no actor is holding this object.
	 */
	UFUNCTION(BlueprintCallable, Category = "States")
	ASuicidalController* GetHolder() const;

	/*
	 * Sets the holder actor to the provided value.
	 *
	 * @param holderActor The actor that is now holding on this object.
	 */
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void PickUp(ASuicidalController* const holderActor);

	/*
	 * Resets the holder actor to NULL.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Drop();

	/*
	 * Event called when this object has been picked up.
	 *
	 * @param holderActor The actor that is now holding on this object.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Actions")
	void OnPickedUp(ASuicidalController* holderActor);

	/*
	 * Event called when this object has been dropped.
	 *
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Actions")
	void OnDropped();
};
