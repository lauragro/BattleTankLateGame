// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* MyWheel = nullptr;

	// Constrains the Wheel and the Base
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* MyAxel = nullptr;

	// Constrains the Axel and the Wheel
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxelWheelConstraint = nullptr;

	virtual void BeginPlay() override;

private:
	void SetupWheel();
	void SetupPhysicsConstraints();

	FConstrainComponentPropName* WheelName = new FConstrainComponentPropName();
};
