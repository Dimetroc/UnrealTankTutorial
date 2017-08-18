// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)){ return;}
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{	
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	FVector LookPosition, LookDirection;
	OutHitLocation = FVector(0.0f);

	if (!GetLookDirectionAndPosition(LookDirection, LookPosition))
	{
		return false;
	}

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, LookPosition, LookPosition + LookDirection*LineTraceRange, ECollisionChannel::ECC_Camera))
	{
		OutHitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Object: %s, is hit at: %s"), *HitResult.Actor->GetName(), *HitResult.ImpactPoint.ToString());
		return true;
	}

	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		PossessedTank->TankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

bool ATankPlayerController::GetLookDirectionAndPosition(FVector& LookDirection, FVector& LookPosition) const
{
	auto ScreenLocation = GetCrossHairSceenLoaction();
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, LookPosition, LookDirection);
}

FVector2D ATankPlayerController::GetCrossHairSceenLoaction() const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
}



