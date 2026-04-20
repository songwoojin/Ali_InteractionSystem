// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ISInteractable.h"
#include "ISInteractableActor.generated.h"

class USphereComponent;

UCLASS()
class INTERACTIONSYSTEM_API AISInteractableActor : public AActor,public IISInteractable
{
	GENERATED_BODY()
	
public:	
	AISInteractableActor();
	virtual void Interact(AActor* Interactor) override;
	virtual EIsInteractionType GetInteractionType() override;

protected:
	virtual void BeginPlay() override;

	void PlayInteractionSound();
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultScenComponent;
	
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* StaticMesh;
    
    UPROPERTY(EditAnywhere)
    USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	USoundBase* InteractionSound;

	UPROPERTY(EditAnywhere)
	EIsInteractionType EIsInteractionType;
};
