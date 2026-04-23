// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ISNPC.h"
#include "Components/SphereComponent.h"
#include "Enum/ISInteractionType.h"
#include "Kismet/GameplayStatics.h"

AISNPC::AISNPC()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetMesh());

	InteractionLocation=CreateDefaultSubobject<USphereComponent>(TEXT("InteractionLocation"));
	InteractionLocation->SetupAttachment(GetMesh());
}

void AISNPC::Interact(AActor* Interactor)
{
	FVector Direction=(Interactor->GetActorLocation()-GetActorLocation()).GetSafeNormal();
	FRotator LookAtRot=Direction.Rotation();
	SetActorRotation(FRotator(0.0f,LookAtRot.Yaw,0.0f));

	PlayInteractionSound();
}

EIsInteractionType AISNPC::GetInteractionType()
{
	return EIsInteractionType::Press;
}

float AISNPC::GetHoldDuration()
{
	return 0.0f;
}

FText AISNPC::GetInteractionPrompt()
{
	return FText::FromString("to talk");
}

int32 AISNPC::GetTapCount()
{
	return 4;
}

FVector AISNPC::GetInteractionLocation()
{
	return InteractionLocation->GetComponentLocation();
}

void AISNPC::BeginPlay()
{
	Super::BeginPlay();	
}

void AISNPC::PlayInteractionSound()
{
	if (!InteractionSound)	return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractionSound, GetActorLocation());
}

void AISNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

