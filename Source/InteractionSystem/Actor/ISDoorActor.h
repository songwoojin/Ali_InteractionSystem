// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/ISInteractableActor.h"
#include "Components/TimelineComponent.h"
#include "ISDoorActor.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API AISDoorActor : public AISInteractableActor
{
	GENERATED_BODY()

public:
	AISDoorActor();
	virtual void Interact(AActor* Interactor) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void OpenDoor();
	void CloseDoor();

protected:
	
private:
	bool bIsOpen;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorCurve;
	
	FTimeline DoorOpenTimeline;

	FRotator ClosedRotation;
	FRotator OpenRotation;

	UFUNCTION()
	void OnDoorUpdate(float Value);
};
