// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float ThrottleValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Throttle %s"), *(FString::SanitizeFloat(ThrottleValue)));

	auto ForceApplied = GetForwardVector() * ThrottleValue * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}
