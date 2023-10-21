// Fill out your copyright notice in the Description page of Project Settings.


#include "MyZombieAreaMainCharacter.h"

// Sets default values
AMyZombieAreaMainCharacter::AMyZombieAreaMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyZombieAreaMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyZombieAreaMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyZombieAreaMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMyZombieAreaMainCharacter::JumpAction);
	PlayerInputComponent->BindAction("MainAction", EInputEvent::IE_Pressed, this, &AMyZombieAreaMainCharacter::MainAction);
	PlayerInputComponent->BindAction("SecondaryAction", EInputEvent::IE_Pressed, this, &AMyZombieAreaMainCharacter::SecondaryAction);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyZombieAreaMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveBackward", this, &AMyZombieAreaMainCharacter::MoveBackward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AMyZombieAreaMainCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyZombieAreaMainCharacter::MoveRight);
}

void AMyZombieAreaMainCharacter::JumpAction()
{
	AddMovementInput(JumpDirection, JumpForce, false);
}

void AMyZombieAreaMainCharacter::MainAction()
{
	// Do something like firing
}

void AMyZombieAreaMainCharacter::SecondaryAction()
{
	// Do something like aiming
}

void AMyZombieAreaMainCharacter::MoveForward(float Input)
{
	FRotator Rotator = GetControlRotation();
	double Force = Input * ForwardMovingSpeed;

	AddMovementInput(FVector(Rotator.Yaw, 0, 0), Force, false);
}

void AMyZombieAreaMainCharacter::MoveBackward(float Input)
{
	FRotator Rotator = GetControlRotation();
	double Force = Input * BackwardMovingSpeed;

	AddMovementInput(FVector(Rotator.Yaw, 0, 0), -Force, false);
}

void AMyZombieAreaMainCharacter::MoveLeft(float Input)
{
	FRotator Rotator = GetControlRotation();
	double Force = Input * SideMovingSpeed;

	AddMovementInput(FVector(0, Rotator.Pitch, 0), -Force, false);
}

void AMyZombieAreaMainCharacter::MoveRight(float Input)
{
	FRotator Rotator = GetControlRotation();
	double Force = Input * SideMovingSpeed;

	AddMovementInput(FVector(0, Rotator.Pitch, 0), Force, false);
}
