// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositioner.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPositioner::UWorldPositioner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPositioner::BeginPlay()
{
	Super::BeginPlay();

	/*UE_LOG(LogTemp, Warning, TEXT("BeginPlayWarning"));
	UE_LOG(LogTemp, Error, TEXT("BeginPlayError"));
	UE_LOG(LogTemp, Display, TEXT("BeginPlayDisplay"));*/

	AActor* Owner = GetOwner();
	FString ObjectName = Owner->GetName();
	FVector ObjectPos = Owner->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("%s is at position X:%f Y:%f Z:%f"), *ObjectName, ObjectPos.X, ObjectPos.Y, ObjectPos.Z);


}


// Called every frame
void UWorldPositioner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

