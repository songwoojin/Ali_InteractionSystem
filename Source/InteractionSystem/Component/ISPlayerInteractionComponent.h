// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ISPlayerInteractionComponent.generated.h"

class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSYSTEM_API UISPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UISPlayerInteractionComponent();

	void ExecuteInteraction();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	UFUNCTION()
	void OnNotifyInteractBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload);

	void RenderInteractionWidget();

	AActor* GetActiveInteractable();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> InteractablesInRange;

	UPROPERTY()
	ACharacter* Character;

	UPROPERTY(EditAnywhere,  Category="ISSettings|Animation")
	UAnimMontage* InteractionMontage;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* InteractionWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "ISSettings|UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY()
	UUserWidget* InteractionWidget;
};
