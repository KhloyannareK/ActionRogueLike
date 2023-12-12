// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarel.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AExplosiveBarel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* radialForce;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;

};
