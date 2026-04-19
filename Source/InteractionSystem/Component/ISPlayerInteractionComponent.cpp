// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ISPlayerInteractionComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interface/ISInteractable.h"

UISPlayerInteractionComponent::UISPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UISPlayerInteractionComponent::ExecuteInteraction()
{
	if (InteractionMontage)
	{
		UAnimInstance* AnimInstance=Character->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			// 노티파이 이름으로 직접 수신!
			// AddDynamic 대신 — 이미 바인딩되어 있으면 중복 추가 안 함
			if (!AnimInstance->OnPlayMontageNotifyBegin.IsAlreadyBound(this, &UISPlayerInteractionComponent::OnNotifyInteractBegin))
			{
				AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UISPlayerInteractionComponent::OnNotifyInteractBegin);
			}
			AnimInstance->Montage_Play(InteractionMontage);
		}
	}
}

void UISPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Character= Cast<ACharacter>(GetOwner());
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

void UISPlayerInteractionComponent::OnNotifyInteractBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	if (InteractablesInRange.IsEmpty())	return;
	
	if (NotifyName == FName("Interact")) // 몽타주 노티파이 이름과 매칭
	{
		AActor* InteractableActor =InteractablesInRange[0];
		
		IISInteractable* Interactable = Cast<IISInteractable>(InteractableActor);
		if (Interactable)
		{
			Interactable->Interact(GetOwner());
		}
	}
}

