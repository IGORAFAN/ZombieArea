// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieAreaCharacter.h"
#include "MyZombieAreaMainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAREA_API AMyZombieAreaMainCharacter : public AZombieAreaCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyZombieAreaMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void JumpAction();

	void MainAction();

	void SecondaryAction();

	void MoveForwardBackward(float Input);

	void MoveLeftRight(float Input);

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup|Jump")
	FVector JumpDirection;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup|Jump")
	float JumpForce;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup|Moving")
	float ForwardMovingSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup|Moving")
	float BackwardMovingSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup|Moving")
	float SideMovingSpeed;
};
