// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGamePlayInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyItemChest.generated.h"


UCLASS()
class ACTIONROGUELIKE_API AMyItemChest : public AActor, public IMyGamePlayInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float upChestPitch;

    // overriding interface from IMyGamePlayInterface - adding _Implementation because the UFunction attribute is set to BlprtNative in the interface
	void interact_Implementation(APawn* pawn);

public:	
	// Sets default values for this actor's properties
	AMyItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* upMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
