// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/ISInteractableActor.h"
#include "IsPickUpItemActor.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API AIsPickUpItemActor : public AISInteractableActor
{
	GENERATED_BODY()
public:
	virtual void Interact(AActor* Interactor) override;


};
