// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ISPlayerInteractionComponent.h"
#include "Character/InteractionSystemCharacter.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interface/ISInteractable.h"
#include "Components/WidgetComponent.h"
#include "Enum/ISInteractionType.h"
#include "UI/ISInteractionWidget.h"
#include "Kismet/GameplayStatics.h"

UISPlayerInteractionComponent::UISPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InteractionWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
}

void UISPlayerInteractionComponent::ExecuteInteraction()
{
	if (!GetActiveInteractable())	return;

	if (IISInteractable* Interactable = Cast<IISInteractable>(GetActiveInteractable()))
	{
		switch(Interactable->GetInteractionType())
		{
		case EIsInteractionType::Press:
			{
				InteractWithActiveInteractable();
				break;
			}
		case EIsInteractionType::Hold:
			{
				if (AInteractionSystemCharacter* ISCharacter=Cast<AInteractionSystemCharacter>(Character))
				{
					ISCharacter->OnInteractionPressOngoing.AddDynamic(this,&UISPlayerInteractionComponent::OnInteractionOngoing);
					ISCharacter->OnInteractionEnd.AddDynamic(this,&UISPlayerInteractionComponent::ResetWidgetProgress);
				}
				break;
			}
		case EIsInteractionType::Tap:
			{
				InteractionTap();
				break;
			}
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

	//InteractionWidgetComponent->AttachToComponent(Character->GetRootComponent(FAttachmentTransformRules::KeepRelativeTransform);
	InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 항상 카메라를 향함
	InteractionWidgetComponent->SetDrawSize(FVector2D(250.f, 30.f));
	//InteractionWidgetComponent->SetVisibility(false); // 기본은 숨김
	
}

void UISPlayerInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->Implements<UISInteractable>())
	{
		InteractablesInRange.AddUnique(OtherActor);
		RenderInteractionWidget();
	}
}

void UISPlayerInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UISInteractable>())
	{
		if (GetActiveInteractable()==OtherActor)
		{
			ResetInteractionState();
		}
		InteractablesInRange.Remove(OtherActor);
		RenderInteractionWidget();
	}
}

void UISPlayerInteractionComponent::OnNotifyInteractBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	if (!GetActiveInteractable())	return;
	
	if (NotifyName == FName("Interact")) // 몽타주 노티파이 이름과 매칭
	{
		IISInteractable* Interactable = Cast<IISInteractable>(GetActiveInteractable());
		if (Interactable)
		{
			Interactable->Interact(GetOwner());
			RenderInteractionWidget();
			ResetInteractionState();
		}
	}
}

void UISPlayerInteractionComponent::RenderInteractionWidget()
{
	if(!GetActiveInteractable())
	{
		InteractionWidgetComponent->SetWidget(nullptr);
	}
	else
	{
		if (InteractionWidgetClass)
		{
			InteractionWidget=CreateWidget<UISInteractionWidget>(GetWorld(),InteractionWidgetClass);
			if (InteractionWidget)
			{
				if (IISInteractable* ISInteractable = Cast<IISInteractable>(GetActiveInteractable()))
				{
					EIsInteractionType IsInteractionType = ISInteractable->GetInteractionType();
					InteractionWidget->SetInteractionType(IsInteractionType);
					
					FText InteractionPromptText = ISInteractable->GetInteractionPrompt();
					InteractionWidget->SetInteractionPromptText(InteractionPromptText);

					InteractionWidgetComponent->SetWidget(InteractionWidget);

					FVector InteractionLocation=ISInteractable->GetInteractionLocation();
					InteractionWidgetComponent->SetWorldLocation(InteractionLocation);
				}
			}
			
		}	
	}
}

AActor* UISPlayerInteractionComponent::GetActiveInteractable()
{
	if (InteractablesInRange.IsEmpty())	return nullptr;

	AActor* LastInteractableActor = InteractablesInRange.Last();

	return LastInteractableActor;
}

void UISPlayerInteractionComponent::InteractWithActiveInteractable()
{
	if (!GetActiveInteractable())	return;

	FaceWithTarget();
	
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

void UISPlayerInteractionComponent::FaceWithTarget()
{
	if (IISInteractable* ISInteractable = Cast<IISInteractable>(GetActiveInteractable()))
	{
		FVector InteractionLocation=ISInteractable->GetInteractionLocation();
		FVector Direction=(InteractionLocation-Character->GetActorLocation()).GetSafeNormal();
		FRotator LookAtRot=Direction.Rotation();
		GetOwner()->SetActorRotation(FRotator(0.0f,LookAtRot.Yaw,0.0f));
	}
}

void UISPlayerInteractionComponent::OnInteractionOngoing(float ElapsedSeconds)
{
	if (InteractionWidget)
	{
		if (IISInteractable* ISInteractable = Cast<IISInteractable>(GetActiveInteractable()))
		{
			float HoldeDuration = ISInteractable->GetHoldDuration();
			float Percent=ElapsedSeconds/HoldeDuration;
			InteractionWidget->SetProgressPercent(Percent);

			if (ElapsedSeconds > HoldeDuration)
			{
				InteractWithActiveInteractable();
				if (AInteractionSystemCharacter* ISCharacter=Cast<AInteractionSystemCharacter>(Character))
				{
					ISCharacter->OnInteractionPressOngoing.RemoveDynamic(this,&UISPlayerInteractionComponent::OnInteractionOngoing);
				}
			}
		}
	}
	
}

void UISPlayerInteractionComponent::InteractionTap()
{
	if (!InteractionTapSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractionTapSound, Character->GetActorLocation());
	}

	CurrentTapCount++;
	
	if (IISInteractable* ISInteratable = Cast<IISInteractable>(GetActiveInteractable()))
	{
		int32 MaxCount=ISInteratable->GetTapCount();
		
		if (CurrentTapCount<=0)
		{
			InteractWithActiveInteractable();
		}
		else
		{
			if (IsValid(InteractionWidget))
			{
				float Percent=static_cast<float>(CurrentTapCount)/MaxCount;
				InteractionWidget->SetProgressPercent(Percent);
			}

			if (CurrentTapCount>=MaxCount)
			{
				InteractWithActiveInteractable();
			}
		}
	}
}

void UISPlayerInteractionComponent::ResetInteractionState()
{
	AInteractionSystemCharacter* ISCharacter=Cast<AInteractionSystemCharacter>(Character);
	{
		ISCharacter->OnInteractionPressOngoing.RemoveDynamic(this,&UISPlayerInteractionComponent::OnInteractionOngoing);
	}

	CurrentTapCount=0;
}

void UISPlayerInteractionComponent::ResetWidgetProgress()
{
	if (IsValid(InteractionWidget))
	{
		InteractionWidget->SetProgressPercent(0);
		if (AInteractionSystemCharacter* ISCharacter=Cast<AInteractionSystemCharacter>(Character))
		{
			ISCharacter->OnInteractionEnd.RemoveDynamic(this,&UISPlayerInteractionComponent::ResetWidgetProgress);
		}
	}
}

void UISPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


