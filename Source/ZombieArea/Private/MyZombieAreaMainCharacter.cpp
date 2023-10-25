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

	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMyZombieAreaMainCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AMyZombieAreaMainCharacter::MoveLeftRight);
}

void AMyZombieAreaMainCharacter::JumpAction()
{
	GetMoveComponent()->
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

void AMyZombieAreaMainCharacter::MoveForwardBackward(float Input)
{
	double Force = Input * ForwardMovingSpeed;
	FRotator Rotator = GetControlRotation();
	FVector Vectors[3];
	FRotationMatrix(Rotator).GetScaledAxes(Vectors[0], Vectors[1], Vectors[2]);
	FMatrix RotMatrix(Vectors[0], Vectors[1], Vectors[2], FVector::ZeroVector);
	FRotator RotatorFromMatrix = RotMatrix.Rotator();
	FVector PitchVector = Rotator.Vector();
	AddMovementInput(PitchVector, Force, false);
}

void AMyZombieAreaMainCharacter::MoveLeftRight(float Input)
{
	double Force = Input * SideMovingSpeed;
	FRotator Rotator = GetControlRotation();
	FVector Vectors[3];
	FRotationMatrix(Rotator).GetScaledAxes(Vectors[0], Vectors[1], Vectors[2]);
	FMatrix RotMatrix(Vectors[0], Vectors[1], Vectors[2], FVector::ZeroVector);
	FRotator RotatorFromMatrix = RotMatrix.Rotator();
	FVector YawVector = FRotationMatrix(RotatorFromMatrix).GetScaledAxis(EAxis::Y);
	AddMovementInput(YawVector, Force, false);
}
