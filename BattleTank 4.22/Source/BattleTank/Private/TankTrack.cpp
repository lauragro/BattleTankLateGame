// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//TODO clamp actual throttle value to [-1,1]
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	/// Spreading out this logic because UE4 was crashing here
	auto Owner = GetOwner();
	if (ensure(Owner))
	{
		auto Root = Owner->GetRootComponent();
		if (ensure(Root))
		{
			auto TankRoot = Cast<UPrimitiveComponent>(Root);
			if (ensure(TankRoot))
			{
				TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
			}
		}
	}
}

void UTankTrack::ApplySidewaysForce()
{
	// Work out required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Apply the opposite force to stop the tank from slipping
	if (SlippageSpeed > 0.0 || SlippageSpeed < 0.0)
	{
		auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

		// F = ma
		auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 4.0;  // Two tracks, half slippage allowed
		TankRoot->AddForce(CorrectionForce);
	}
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}
