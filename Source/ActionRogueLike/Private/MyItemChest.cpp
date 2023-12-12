// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemChest.h"


// Sets default values
AMyItemChest::AMyItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseChestMesh");
	RootComponent = baseMesh;

	upMesh = CreateDefaultSubobject<UStaticMeshComponent>("upChestMesh");
	upMesh->SetupAttachment(baseMesh);

	upChestPitch = 110.0;

}

void AMyItemChest::interact_Implementation(APawn* pawn)
{
	UE_LOG(LogTemp, Log, TEXT("interact_implementation in chest"));
	upMesh->SetRelativeRotation(FRotator{ upChestPitch, 0, 0 });
}


// Called when the game starts or when spawned
void AMyItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

