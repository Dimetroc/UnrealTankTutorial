#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
		if (!ensure(LeftTrack) || !ensure(RightTrack) || Throw == 0.0f)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack) || Throw == 0.0f)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s, AIForwardIntention: %s"), *(GetOwner()->GetName()), *AIForwardIntention.ToString());
	auto Forward = FVector::DotProduct(TankForward, AIForwardIntention);
	auto Right = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	LeftTrack->SetThrottle(Forward + Right);
	RightTrack->SetThrottle(Forward - Right);
}


