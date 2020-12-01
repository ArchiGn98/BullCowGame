// Copyright Artur Hnoinskyi 2020


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	FindInputComponent();
}

// check for physics handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Grabber component, but no Physics Handle component"), *GetOwner()->GetName());
	}
}

// check for Input Component
void UGrabber::FindInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has Input component"), *GetOwner()->GetName());
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Grabber component, but no Input Handle component"), *GetOwner()->GetName());
	}
}

std::pair<FVector, FRotator> UGrabber::GetPlayersViewPoint() const
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	

	return std::make_pair(PlayerViewPointLocation, PlayerViewPointRotation);
}

FVector UGrabber::GetPlayersReach(std::pair<FVector, FRotator> ViewPoint) const
{
	FVector LineTraceDirection = ViewPoint.second.Vector();
	FVector LineTraceEnd = ViewPoint.first + LineTraceDirection * Reach;

	return LineTraceEnd;
}

void UGrabber::Grab()
{
	if (Input)
	{
		FVector LineTraceEnd = GetPlayersReach(GetPlayersViewPoint());

		UE_LOG(LogTemp, Warning, TEXT("%s Grab()"), *GetOwner()->GetName());
		FHitResult HitResult =  GetFirstPhysicsBodyInReach();

		// TODO: Attach physics handle
		if (HitResult.GetActor())
		{
			PhysicsHandle->GrabComponentAtLocation(HitResult.GetComponent(), NAME_None, LineTraceEnd);
		}
	}
}

void UGrabber::Release()
{
	if (Input)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Release()"), *GetOwner()->GetName());
		//TODO: remove/release physics handle
		PhysicsHandle->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached 
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector LineTraceEnd = GetPlayersReach(GetPlayersViewPoint());
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}	
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Ray-cast out to certain distance (Reach)
	FHitResult Hit;

	/**
	*param2 - Use player collision or visibility collision;
	*param3 - Ignore owner object in collision
	*/
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersViewPoint().first,
		GetPlayersReach(GetPlayersViewPoint()),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}