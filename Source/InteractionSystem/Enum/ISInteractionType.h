// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISInteractionType.generated.h" // 이게 반드시 있어야 함

/**
 * 
 */
UENUM(BlueprintType) // 이 매크로를 사용하면 블루프린트에서 사용할 수 있습니다.
enum class EIsInteractionType  : uint8 // uint8 타입을 사용하는 것이 좋습니다.
{
    Press     UMETA(DisplayName = "Press"),
    Hold  UMETA(DisplayName = "Hold"),
    Tap  UMETA(DisplayName = "Tap"),
};
