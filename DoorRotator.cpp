// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorRotator.h"

// Sets default values for this component's properties
UDoorRotator::UDoorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorRotator::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator TargetRotation = OriginalRotation;

	if(ShouldRotate){
		TargetRotation = OriginalRotation + RotateOffset;
		// UE_LOG(LogTemp, Display, TEXT("Original: %s Offset: %s"), *OriginalRotation.ToString(), *RotateOffset.ToString());
		UE_LOG(LogTemp, Display, TEXT("Rotating %s: %s"), *GetOwner()->GetActorNameOrLabel(), *TargetRotation.ToString());
	}

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotateTime);
	// UE_LOG(LogTemp, Display, TEXT("Current Rotation: %s"), *NewRotation.ToString());
	GetOwner()->SetActorRotation(NewRotation);
}

void UDoorRotator::SetShouldRotate(bool NewRotate)
{
	ShouldRotate = NewRotate;
}