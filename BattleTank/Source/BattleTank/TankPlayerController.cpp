// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	if(ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank pawn %s found"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank pawn not found!"));
	}

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming component not found!"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(ControlledTank)){ return;}
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{	
		ControlledTank->AimAt(HitLocation);
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

	if (GetWorld()->LineTraceSingleByChannel(HitResult, LookPosition, LookPosition + LookDirection*LineTraceRange, ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Object: %s, is hit at: %s"), *HitResult.Actor->GetName(), *HitResult.ImpactPoint.ToString());
		return true;
	}

	return false;
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



