// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if(Mover && Actor)
	{
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(component)
		{
			component->SetSimulatePhysics(false);			
		}

		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		// UE_LOG(LogTemp, Display, TEXT("Moving Actor"));
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for(AActor* Actor : Actors)
	{
		if(Actor->ActorHasTag(tagName) && !Actor->ActorHasTag("Grabbed"))
		{
			// UE_LOG(LogTemp, Display, TEXT("Actor Unlocking: %s"), *Actor->GetActorNameOrLabel());
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

