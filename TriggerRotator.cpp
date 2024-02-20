// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerRotator.h"

// Sets default values for this component's properties
UTriggerRotator::UTriggerRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTriggerRotator::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTriggerRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if(Rotator && Actor)
	{
		// UE_LOG(LogTemp, Display, TEXT("Rotating Actor"));
		Rotator->SetShouldRotate(true);
	}
	else
	{
		Rotator->SetShouldRotate(false);
	}
}

AActor* UTriggerRotator::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for(AActor* Actor : Actors)
	{
		if(Actor->ActorHasTag(tagName))
		{
			UE_LOG(LogTemp, Display, TEXT("Actor Opening: %s"), *Actor->GetActorNameOrLabel());
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerRotator::SetRotator(UDoorRotator* NewRotator)
{
	Rotator = NewRotator;
}