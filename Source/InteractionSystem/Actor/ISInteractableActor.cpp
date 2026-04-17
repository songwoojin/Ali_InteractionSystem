// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ISInteractableActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AISInteractableActor::AISInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	//StaticMesh->SetupAttachment(SphereComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

void AISInteractableActor::Interact(AActor* Interactor)
{
	PlayInteractionSound();
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

