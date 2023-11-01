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

	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		LastMeshRotation = MeshComponent->GetRelativeLocation().Rotation();
	}
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
	Jump();
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
	//double Force = Input * ForwardMovingSpeed;
	//FRotator Rotator = GetControlRotation();
	//FVector Vectors[3];
	//FRotationMatrix(Rotator).GetScaledAxes(Vectors[0], Vectors[1], Vectors[2]);
	//FMatrix RotMatrix(Vectors[0], Vectors[1], Vectors[2], FVector::ZeroVector);
	//FRotator RotatorFromMatrix = RotMatrix.Rotator();
	//FVector PitchVector = Rotator.Vector();
	//AddMovementInput(PitchVector, Force, false);
	//RotateCharacterMeshByMoveVector(FRotator(0, 1, 0));

	if (Controller && Input != 0.0f)
	{
		// Получите направление движения от контроллера и вектор вперед от него
		const FRotator ControllerRotation = Controller->GetControlRotation();
		const FRotator ForwardRotation = FRotator(0.0f, ControllerRotation.Yaw, 0.0f);
		const FVector ForwardVector = FRotationMatrix(ForwardRotation).GetUnitAxis(EAxis::X);

		FRotator NewRotation = ForwardVector.Rotation();

		// Примените движение вперед
		const FVector Direction = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Input);

		//SetActorRotation(NewRotation);
		
		// Поворот персонажа в сторону движения
		if (USkeletalMeshComponent* MeshComponent = GetMesh())
		{	
			NewRotation = Input >= 0 ? FRotator(0.f, 0.f, 0.f) : FRotator(0.f, 180.f, 0.f);
			if (!FMath::IsNearlyEqual(LastMeshRotation.Yaw, NewRotation.Yaw, 10))
			{
				MeshComponent->AddLocalRotation(NewRotation);
				LastMeshRotation = NewRotation;
			}
		}
	}
}

void AMyZombieAreaMainCharacter::MoveLeftRight(float Input)
{
	//double Force = Input * SideMovingSpeed;
	//FRotator Rotator = GetControlRotation();
	//FVector Vectors[3];
	//FRotationMatrix(Rotator).GetScaledAxes(Vectors[0], Vectors[1], Vectors[2]);
	//FMatrix RotMatrix(Vectors[0], Vectors[1], Vectors[2], FVector::ZeroVector);
	//FRotator RotatorFromMatrix = RotMatrix.Rotator();
	//FVector YawVector = FRotationMatrix(RotatorFromMatrix).GetScaledAxis(EAxis::Y);
	//AddMovementInput(YawVector, Force, false);
	//RotateCharacterMeshByMoveVector(FRotator(0, 1, 0));
	
	if (Controller && Input != 0.0f)
	{
		// Получите направление движения от контроллера и вектор вперед от него
		const FRotator ControllerRotation = Controller->GetControlRotation();
		const FRotator RightRotation = FRotator(ControllerRotation.Pitch, 0.0f, 0.0f);
		const FVector RightVector = FRotationMatrix(RightRotation).GetUnitAxis(EAxis::Y);

		FRotator NewRotation = RightVector.Rotation();
		
		// Примените движение вперед
		const FVector Direction = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Input);
		
		//SetActorRotation(NewRotation);
		
		// Поворот персонажа в сторону движения
		if (USkeletalMeshComponent* MeshComponent = GetMesh())
		{
			NewRotation = Input >= 0 ? FRotator(0.f, 90.f, 0.f) : FRotator(0.f, -90.f, 0.f);
			if (!FMath::IsNearlyEqual(LastMeshRotation.Yaw, NewRotation.Yaw, 10))
			{
				MeshComponent->AddLocalRotation(NewRotation);
				LastMeshRotation = NewRotation;
			}
		}
	}
}
