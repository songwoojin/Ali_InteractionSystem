// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/ISInteractionType.h"
#include "ISInteractionWidget.generated.h"

/**
 * 
 */

class UProgressBar;

UCLASS()
class INTERACTIONSYSTEM_API UISInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInteractionType(EIsInteractionType InInteractionType);
	
	UFUNCTION(BlueprintPure)
	EIsInteractionType GetInteractionType() const { return InteractionType; }

	void SetProgressPercent(float InPercent);

	void SetInteractionPromptText(FText PromptText);

	UFUNCTION(BlueprintPure)
	FText GetInteractionPromptText() const { return InteractionPromptText; }
	
protected:
	EIsInteractionType InteractionType;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess="true",BindWidget))
	TObjectPtr<UProgressBar> InteractionProgressBar;

	FText InteractionPromptText;
};
