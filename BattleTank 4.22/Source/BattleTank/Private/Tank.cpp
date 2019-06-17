// Copyright N/A

#include "Tank.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	// TODO call once we declare it
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageAmount;
}

float ATank::GetHealthPercent()
{
	return (float)CurrentHealth / (float)MaxHealth;
}



