// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(!Barrel){return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, aiming at: %s"), *(GetOwner()->GetName()), *AimDirection.ToString());
		MoveBarrelTowerds(AimDirection);
	}else
	{
		MoveBarrelTowerds(FVector(0.0f));
	}
}

void UTankAimingComponent::MoveBarrelTowerds(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAtRotation = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
}