// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Classes/Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points since added at construction
	ProjectileMoving = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMoving->bAutoActivate = false;
	
	ColliderMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collider Mesh"));
	SetRootComponent(ColliderMesh);
	ColliderMesh->SetNotifyRigidBodyCollision(true);
	ColliderMesh->SetVisibility(false);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->bIgnoreOwningActor = true;
	ExplosionForce->Radius = 400;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ColliderMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMoving->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMoving->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("On Projectile Hit!"));

	// Turn off launch blast
	LaunchBlast->Deactivate();

	// Turn on impact blast
	ImpactBlast->Activate();

	// Apply impulse to the object hit
	ExplosionForce->FireImpulse();

	// Set new parent, then destroy collision component
	SetRootComponent(ImpactBlast);
	ColliderMesh->DestroyComponent();
	
	// Damage hit target
	UGameplayStatics::ApplyRadialDamage
	(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,  // For consistency
		UDamageType::StaticClass(),
		TArray<AActor*>()        // All actors
	);

	// Destroy self after enough time, to keep world clean
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay);
}

void  AProjectile::OnTimerExpire()
{
	Destroy();
}
