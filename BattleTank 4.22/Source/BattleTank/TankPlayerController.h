// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimingComponentReference);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LineTraceRange = 1000000.0; // cm

	void BeginPlay() override;

	UFUNCTION()
	void OnPossessedTankDeath();

private:

	void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

	// Start the tank moving the barrel so that a bullet would hit
	// where the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, TRUE if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
