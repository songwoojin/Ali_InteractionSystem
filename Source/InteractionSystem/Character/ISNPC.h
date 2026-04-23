// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ISInteractable.h"
#include "ISNPC.generated.h"

class USphereComponent;

UCLASS()
class INTERACTIONSYSTEM_API AISNPC : public ACharacter ,public IISInteractable
{
	GENERATED_BODY()

public:
	AISNPC();
	virtual void Interact(AActor* Interactor) override;
	virtual EIsInteractionType GetInteractionType() override;
	virtual float GetHoldDuration() override;
	virtual FText GetInteractionPrompt() override;
	virtual int32 GetTapCount() override;
	virtual FVector GetInteractionLocation() override;
	
protected:
	virtual void BeginPlay() override;
	void PlayInteractionSound();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	USoundBase* InteractionSound;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionLocation;
};
