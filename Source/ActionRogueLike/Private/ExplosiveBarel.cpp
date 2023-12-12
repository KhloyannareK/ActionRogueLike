// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AExplosiveBarel::AExplosiveBarel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = mesh;
	mesh->SetSimulatePhysics(true);
	// Enabling Simulate physics automatically changes the Profile to PhysicsActor in Blueprint, in C++ we need to change this manually.
	mesh->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	radialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	radialForce->SetupAttachment(mesh);


	radialForce->SetAutoActivate(false);

	radialForce->Radius = 750.0f;
	radialForce->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	radialForce->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	radialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void AExplosiveBarel::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentHit.AddDynamic(this, &AExplosiveBarel::OnHitEvent);
}


// Called every frame
void AExplosiveBarel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarel::OnHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Hit event"));
	radialForce->FireImpulse();

}

