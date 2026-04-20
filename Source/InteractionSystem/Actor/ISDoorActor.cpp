// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ISDoorActor.h"

#include "Enum/ISInteractionType.h"

AISDoorActor::AISDoorActor()
	:bIsOpen(false)
{
}

void AISDoorActor::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);
	
	if (bIsOpen)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}
}

void AISDoorActor::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve)
	{
		ClosedRotation = StaticMesh->GetRelativeRotation();
		OpenRotation = ClosedRotation + FRotator(0.f, 90.f, 0.f);
		
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("OnDoorUpdate"));

		DoorOpenTimeline.AddInterpFloat(DoorCurve, ProgressFunction);
	}
}

void AISDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DoorOpenTimeline.TickTimeline(DeltaTime);
}

void AISDoorActor::OpenDoor()
{
	bIsOpen = true;

	DoorOpenTimeline.Play();
}

void AISDoorActor::CloseDoor()
{
	bIsOpen = false;

	DoorOpenTimeline.Reverse();
}

void AISDoorActor::OnDoorUpdate(float Value)
{
	FRotator NewRot = FMath::Lerp(ClosedRotation, OpenRotation, Value);
	StaticMesh->SetRelativeRotation(NewRot);

	UE_LOG(LogTemp, Warning, TEXT("OnDoorUpdate"));
}
