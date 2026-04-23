// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ISInteractionWidget.h"
#include "Components/ProgressBar.h"

void UISInteractionWidget::SetInteractionType(EIsInteractionType InInteractionType)
{
	InteractionType = InInteractionType;
}

void UISInteractionWidget::SetProgressPercent(float InPercent)
{
	if (InteractionProgressBar)
	{
		InteractionProgressBar->SetPercent(InPercent);
	}
}

void UISInteractionWidget::SetInteractionPromptText(FText PromptText)
{
	InteractionPromptText = PromptText;
}
