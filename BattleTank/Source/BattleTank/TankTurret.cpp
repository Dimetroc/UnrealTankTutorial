// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto Rotation = RelativeRotation.Yaw + RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation((FRotator(0, Rotation, 0)));
}
