// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Clamp relative speed since -1 and 1 is our expected range
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);

	// Move turret the right amount this frame
	// given max rotation speed and time frame
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}


