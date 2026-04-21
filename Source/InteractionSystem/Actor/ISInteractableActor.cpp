// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ISInteractableActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AISInteractableActor::AISInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultScenComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = DefaultScenComponent;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultScenComponent);
	//StaticMesh->SetupAttachment(SphereComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(StaticMesh);
}

void AISInteractableActor::Interact(AActor* Interactor)
{
	PlayInteractionSound();
}

EIsInteractionType AISInteractableActor::GetInteractionType()
{
	return EIsInteractionType;
}

float AISInteractableActor::GetHoldDuration()
{
	return HoldDuration;
}

void AISInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void AISInteractableActor::PlayInteractionSound()
{
	if (!InteractionSound)	return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractionSound, GetActorLocation());
}

void AISInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

