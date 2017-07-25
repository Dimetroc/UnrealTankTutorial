// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{

}

void UTankTrack::BeginPlay()
{
	PrimaryComponentTick.bCanEverTick = true;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (WasHitLastFrame)
	{
		ApplySidewaysForce();
		DriveTrack();
		CurrentThrottle = 0.0f;
		WasHitLastFrame = false;
	}
}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2.0f;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, DriveTrack: %s, throttle: %s"), *(GetOwner()->GetName()), *(GetName()), *ForceApplied.ToString());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent * Hitcomponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, hit"), *(GetOwner()->GetName()));
	
	WasHitLastFrame = true;
}

void UTankTrack::SetThrottle(float ThrottleValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, Track: %s, throttle: %s"), *(GetOwner()->GetName()), *(GetName()), *FString::SanitizeFloat(ThrottleValue));
	CurrentThrottle = FMath::Clamp<float>(ThrottleValue, -1.0f, 1.0f);
}