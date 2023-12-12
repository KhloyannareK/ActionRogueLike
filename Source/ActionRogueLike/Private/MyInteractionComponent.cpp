// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractionComponent.h"
#include "MyGamePlayInterface.h"


// Sets default values for this component's properties
UMyInteractionComponent::UMyInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMyInteractionComponent::PrimaryInteraction()
{
	// input to line trace
	FCollisionObjectQueryParams collisionParams;
	collisionParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector actorViewPos;
	FRotator actorViewRot;
	GetOwner()->GetActorEyesViewPoint(actorViewPos, actorViewRot);
	FVector start = actorViewPos, end = actorViewRot.Vector() * 1000; // 1000cm to the direction of eye`s view

	/// This is the sphere trace
	TArray<FHitResult> hitResults;
	FCollisionShape collisionShape;
	const float radius = 30.0f;
	collisionShape.SetSphere(radius);
	const bool blocksSth = GetWorld()->SweepMultiByObjectType(hitResults, start, end, FQuat::Identity, collisionParams, collisionShape);
	for (const FHitResult& hitResult : hitResults) {
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, radius, 32, FColor::Green, false, 2.0);
		if (AActor* hitActor = hitResult.GetActor()) {
			UE_LOG(LogTemp, Log, TEXT("DEBUG: PrimaryInteraction found dynamic object to interact"));
			// Our implemented interface 
			if (hitActor->Implements<UMyGamePlayInterface>()) {
				UE_LOG(LogTemp, Log, TEXT("DEBUG: PrimaryInteraction found dynamic object to interact which implements gameplay interface"));
				APawn* pawn = Cast<APawn>(GetOwner());
				// interact() function call view I<interface>
				IMyGamePlayInterface::Execute_interact(hitActor, pawn);
				break;
			}
		}
	}

	/* This is for line trace but not sphere - just left for the example
	// output for line trace
	FHitResult hitResult;
	// pixel size area check
	const bool blocksSth = GetWorld()->LineTraceSingleByObjectType(hitResult, start, end, collisionParams);

	if (AActor* hitActor = hitResult.GetActor()) {
		UE_LOG(LogTemp, Log, TEXT("DEBUG: PrimaryInteraction found dynamic object to interact"));
		// Our implemented interface 
		if (hitActor->Implements<UMyGamePlayInterface>()) {
			UE_LOG(LogTemp, Log, TEXT("DEBUG: PrimaryInteraction found dynamic object to interact which implements gameplay interface"));
			APawn* pawn = Cast<APawn>(GetOwner());
			// interact() function call view I<interface>
			IMyGamePlayInterface::Execute_interact(hitActor, pawn);
		}
	}

	// draws line from start to end in the world
	*/

	DrawDebugLine(GetWorld(), start, end, (blocksSth ? FColor::Red : FColor::Blue), false, 2.0);

}


// Called when the game starts
void UMyInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

