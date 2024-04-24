// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	actorStartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Actor Begin"));
	UE_LOG(LogTemp, Error, TEXT("Actor Begin"));
	UE_LOG(LogTemp, Warning, TEXT("Actor Begin"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);

}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(rotationVelocity * DeltaTime);
}

// Pseudo Code for moving the platform Forward and Backward
// 1 Get the current location of Platform
// 2 Add vector to it to the location in loop
// 3 Check if the destination reach 
// 4 reverse the location to start point
// 5 back to original location , (motion of speed should be faster)
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if(ShouldPlatformReturn()){
		// Move Backward Direction 
		FVector moveDirection = platformVelocity.GetSafeNormal(); // to make safe travel
		actorStartLocation = actorStartLocation +  (moveDirection * platformDistance); // rather than current location we have calculated new location with direction
		SetActorLocation(actorStartLocation);
		// reversing back
		platformVelocity = -platformVelocity;
	}else{
		// Move Forward Direction
		FVector currentLocation = GetActorLocation();
		currentLocation = currentLocation + (platformVelocity * DeltaTime); // to make it independent of Time specific
		SetActorLocation(currentLocation);
	}
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	float diffInDistance = GetDistanceMoved();
	FString actorName = GetName();
	UE_LOG(LogTemp, Display, TEXT("%s Platform Overshoot Distance by %f"), *actorName,(diffInDistance - platformDistance) );
	return diffInDistance > platformDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(actorStartLocation,GetActorLocation());
}

