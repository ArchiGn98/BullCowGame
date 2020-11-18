// Copyright Artur Hnoinskyi 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InterpSpeed = 2.f;
	RotateAngle = 90.f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	TargetYaw = GetOwner()->GetActorRotation().Yaw + RotateAngle;	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);

	FRotator CurrRotation = GetOwner()->GetActorRotation();	
	CurrRotation.Yaw = FMath::FInterpTo(CurrRotation.Yaw, TargetYaw, DeltaTime, InterpSpeed);	
	GetOwner()->SetActorRotation(CurrRotation);
		
	// This method is depends on your computer speed (better pc => faster the door opens)
	// CurrRotation.Yaw = FMath::Lerp(CurrRotation.Yaw, TargetYaw, PrecentageIncrease);
}

