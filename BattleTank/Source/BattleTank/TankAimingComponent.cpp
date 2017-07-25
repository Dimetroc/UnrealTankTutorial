// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel)){return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, aiming at: %s"), *(GetOwner()->GetName()), *AimDirection.ToString());
		MoveBarrelTowerds(AimDirection);
		MoveTurretTowerds(AimDirection);
	}else
	{
		MoveBarrelTowerds(FVector(0.0f));
		MoveTurretTowerds(FVector(0.0f));
	}
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::MoveBarrelTowerds(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAtRotation = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowerds(FVector AimDirection)
{
	auto BarrelRotation = Turret->GetForwardVector().Rotation();
	auto AimAtRotation = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotation - BarrelRotation;
	if (DeltaRotator.Yaw > 180.0f || DeltaRotator.Yaw < -180.0f)
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}
	auto BarrelRotation = Barrel->GetForwardVector();
	return !BarrelRotation.Equals(AimDirection, 0.001f);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringStatus::Reloading)
	{
		if (!ensure(Barrel && ProjectileBlueprint))
		{
			return;
		}

		auto Location = Barrel->GetSocketLocation(FName("Projectile"));
		auto Rotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		LastFireTime = FPlatformTime::Seconds();
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}


