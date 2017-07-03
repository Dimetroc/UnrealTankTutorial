// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	TankBarrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) const
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire()
{
	if(!TankBarrel){ return; }

	auto Location = TankBarrel->GetSocketLocation(FName("Projectile"));
	auto Rotation = TankBarrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);

	Projectile->LaunchProjectile(LaunchSpeed);
}

