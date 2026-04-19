// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ISPlayerInteractionComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interface/ISInteractable.h"

UISPlayerInteractionComponent::UISPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UISPlayerInteractionComponent::Interact()
{
	if (InteractablesInRange.IsEmpty())	return;
	
	AActor* InteractableActor =InteractablesInRange[0];
	
	IISInteractable* Interactable = Cast<IISInteractable>(InteractableActor);
	if (Interactable)
	{
		Interactable->Interact(GetOwner());
	}
}

void UISPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character= Cast<ACharacter>(GetOwner());
	if (Character)
	{
		UCapsuleComponent* PlayerCapsuleComponent = Character->GetCapsuleComponent();
		if (PlayerCapsuleComponent)
		{
			PlayerCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this,&UISPlayerInteractionComponent::OnOverlapBegin);
			PlayerCapsuleComponent->OnComponentEndOverlap.AddDynamic(this,&UISPlayerInteractionComponent::OnOverlapEnd);
		}
	}
	
}

void UISPlayerInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UISInteractable>())
	{
		InteractablesInRange.AddUnique(OtherActor);
	}
}

void UISPlayerInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UISInteractable>())
	{
		InteractablesInRange.Remove(OtherActor);
	}
}

void UISPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

