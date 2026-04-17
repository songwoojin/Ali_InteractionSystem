// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/IsPickUpItemActor.h"

void AIsPickUpItemActor::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);
	
	const FString ItemName = GetName();
	const FString ActorName = Interactor->GetName();
	UE_LOG(LogTemp,Warning,TEXT("Added %s to the inventory of %s"),*ItemName,*ActorName);

	PlayInteractionSound();

	Destroy();
}
