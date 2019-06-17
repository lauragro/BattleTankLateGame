// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossessedTankDeath();
	
protected:
	// How close AI tank will get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 80.0;

private:
	virtual void SetPawn(APawn* InPawn) override;


};
