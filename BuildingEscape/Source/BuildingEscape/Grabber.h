// Copyright Artur Hnoinskyi 2020

#pragma once
#include  <utility>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
private:
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* Input = nullptr;

	//AActor* HittedActor = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void FindInputComponent();

	// Return the first Acror within reach with a Physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	std::pair<FVector, FRotator> GetPlayersViewPoint() const;
	FVector GetPlayersReach(std::pair<FVector, FRotator> ViewPoint) const;
};
