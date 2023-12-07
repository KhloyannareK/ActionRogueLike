// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ForwardAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RightAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnYAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ProjectileAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MappingContext;

	void MoveForward(const FInputActionValue& v);
	void Turn(const FInputActionValue& v);
	void MoveRight(const FInputActionValue& v);
	void MyJump(const FInputActionValue& v);
	void TurnY(const FInputActionValue& v);
	void SpawnProjectile(const FInputActionValue& v);

};
