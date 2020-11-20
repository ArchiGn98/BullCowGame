// Copyright Artur Hnoinskyi 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	InitialYaw = Owner->GetActorRotation().Yaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component, but no pressureplate set"), *Owner->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	/*
	DeltaTime - time between frames being rendered (for 60fps/s == 1/60 == 0.01666s == 16.66ms)
	*/
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("FPS: %f"), 1.f / DeltaTime);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorTrigger))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}		
	}

	if (!ActorTrigger)
	{
		ActorTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();
	}	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	MoveDoor(DeltaTime, InitialYaw + RotateAngle, OpenSpeed);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	MoveDoor(DeltaTime, InitialYaw, CloseSpeed);
}

void UOpenDoor::MoveDoor(float DeltaTime, float Yaw, float Speed)
{
	FRotator CurrRotation = Owner->GetActorRotation();
	CurrRotation.Yaw = FMath::FInterpTo(CurrRotation.Yaw, Yaw, DeltaTime, Speed);
	Owner->SetActorRotation(CurrRotation);
}