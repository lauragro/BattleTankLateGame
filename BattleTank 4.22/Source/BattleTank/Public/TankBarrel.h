// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// +1 for max speed, -1 for negative direction max speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 10.0f; // Sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationDegrees = 0.0f; // Sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 40.0f; // Sensible default
};
