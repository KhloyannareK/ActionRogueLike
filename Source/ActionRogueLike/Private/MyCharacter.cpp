// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// You can bind to any of the trigger events here by changing the "ETriggerEvent" enum value
		Input->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForward);
		Input->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AMyCharacter::Turn);
		Input->BindAction(RightAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveRight);
		Input->BindAction(TurnYAction, ETriggerEvent::Triggered, this, &AMyCharacter::TurnY);
		Input->BindAction(ProjectileAction, ETriggerEvent::Triggered, this, &AMyCharacter::SpawnProjectile);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::MyJump);
		if (APlayerController* PC = Cast<APlayerController>(GetController())) {
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
				Subsystem->ClearAllMappings();

				// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
				Subsystem->AddMappingContext(MappingContext, 0);
			}
		}
	}
	
}

void AMyCharacter::MoveForward(const FInputActionValue& v)
{
	UE_LOG(LogTemp, Log, TEXT("MoveForward"));
	FRotator rotator = GetControlRotation();
	rotator.Pitch = 0.0f;
	rotator.Roll = 0.0f;

	AddMovementInput(rotator.Vector(), v.Get<float>());
}

void AMyCharacter::Turn(const FInputActionValue& v)
{
	UE_LOG(LogTemp, Log, TEXT("Turn"));
	AddControllerYawInput(v.Get<float>());
}

void AMyCharacter::MoveRight(const FInputActionValue& v)
{
	UE_LOG(LogTemp, Log, TEXT("MoveRight"));
	FRotator rotator = GetControlRotation();
	rotator.Pitch = 0.0f;
	rotator.Roll = 0.0f;

	// X - forward
	// Y - right
	// Z - up

	FVector rightVector = FRotationMatrix(rotator).GetScaledAxis(EAxis::Y);

	AddMovementInput(rightVector, v.Get<float>());
}

void AMyCharacter::MyJump(const FInputActionValue& v)
{
	UE_LOG(LogTemp, Log, TEXT("Jump"));
	ACharacter::Jump();
}

void AMyCharacter::TurnY(const FInputActionValue& v)
{
	UE_LOG(LogTemp, Log, TEXT("TurnY"));
	AddControllerPitchInput(v.Get<float>());
}

void AMyCharacter::SpawnProjectile(const FInputActionValue& v)
{
	UE_LOG(LogTemp, Log, TEXT("SpawnProjectile"));

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector handLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform spawnTransform{ GetControlRotation(), handLocation};

	GetWorld()->SpawnActor<AActor>(ProjectileClass, spawnTransform, spawnParameters);
}

