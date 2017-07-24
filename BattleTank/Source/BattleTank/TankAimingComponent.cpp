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

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel)){return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, aiming at: %s"), *(GetOwner()->GetName()), *AimDirection.ToString());
		MoveBarrelTowerds(AimDirection);
		MoveTurretTowerds(AimDirection);
	}else
	{
		MoveBarrelTowerds(FVector(0.0f));
		MoveTurretTowerds(FVector(0.0f));
	}
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

	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		return;
	}
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


