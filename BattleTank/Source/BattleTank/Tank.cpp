// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

void ATank::Initialise(UTankBarrel * BarrelToSet)
{
	TankBarrel = BarrelToSet;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire()
{

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		return;
	}
	if(!TankBarrel){ return; }

	auto Location = TankBarrel->GetSocketLocation(FName("Projectile"));
	auto Rotation = TankBarrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
	LastFireTime = FPlatformTime::Seconds();
	Projectile->LaunchProjectile(LaunchSpeed);
}

