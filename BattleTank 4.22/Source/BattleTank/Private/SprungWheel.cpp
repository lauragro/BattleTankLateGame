// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	PrimaryActorTick.bCanEverTick = true;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Constraint"));
	SetRootComponent(SpringConstraint);

	MyAxel = CreateDefaultSubobject<USphereComponent>(FName("My Axel"));
	MyAxel->SetupAttachment(SpringConstraint);

	AxelWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axel Wheel Constraint"));
	AxelWheelConstraint->SetupAttachment(MyAxel);

	MyWheel = CreateDefaultSubobject<USphereComponent>(FName("My Wheel"));
	MyWheel->SetupAttachment(MyAxel);


}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupWheel();
	SetupPhysicsConstraints();
}

void ASprungWheel::SetupWheel()
{
	MyWheel->SetEnableGravity(true);
	MyWheel->SetSimulatePhysics(true);
}

void ASprungWheel::SetupPhysicsConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, MyAxel, NAME_None);

	AxelWheelConstraint->SetConstrainedComponents(MyAxel, NAME_None, MyWheel, NAME_None);
}

