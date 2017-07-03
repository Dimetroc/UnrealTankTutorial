// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"





void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Elevation = FMath::Clamp( RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation((FRotator(Elevation, 0, 0)));


}
